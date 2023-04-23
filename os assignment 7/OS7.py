import random
import threading
import time
import sys

print("0. Exit")
print("1. Reader Writer")
print("2. Producer Consumer")
print("3. Printer Spooler")
choice = int(input("Enter your choice: "))

if choice == 0:
    sys.exit()
elif choice == 1:
    class ReaderWriter():
        def __init__(self):
            # initializing semaphores using Semaphore class in threading module for reading and wrting
            self.rd = threading.Semaphore()
            self.wrt = threading.Semaphore()
            self.readCount = 0  # initializing number of reader present
        def reader(self):
            while True:
                self.rd.acquire()  # wait on read semaphore
                self.readCount += 1  # increase count for reader by 1
                if self.readCount == 1:  # since reader is present, prevent writing on data
                    self.wrt.acquire()  # wait on write semaphore
                self.rd.release()  # sinal on read semaphore
                print(f"Reader {self.readCount} is reading \n")
                self.rd.acquire()  # wait on read semaphore
                self.readCount -= 1  # reading performed by reader hence decrementing readercount
                if self.readCount == 0:  # if no reader is present allow writer to write the data
                    self.wrt.release()  # signal on write semphore, now writer can write
                self.rd.release()  # sinal on read semaphore
                time.sleep(3)
        def writer(self):
            while True:
                self.wrt.acquire()  # wait on write semaphore
                print("Wrting data.....")  # write the data
                print("-"*20)
                self.wrt.release()  # sinal on write semaphore
                time.sleep(3)
        def main(self):
            # calling mutliple readers and writers
            t1 = threading.Thread(target=self.reader)
            t1.start()
            t2 = threading.Thread(target=self.writer)
            t2.start()
            t3 = threading.Thread(target=self.reader)
            t3.start()
            t4 = threading.Thread(target=self.reader)
            t4.start()
            t6 = threading.Thread(target=self.writer)
            t6.start()
            t5 = threading.Thread(target=self.reader)
            t5.start()

    if __name__ == "__main__":
        c = ReaderWriter()
        c.main()

elif choice == 2:
    # Shared Memory variables
    CAPACITY = 10
    buffer = [-1 for i in range(CAPACITY)]
    in_index = 0
    out_index = 0
    # Declaring Semaphores
    mutex = threading.Semaphore()
    empty = threading.Semaphore(CAPACITY)
    full = threading.Semaphore(0)

    class Producer(threading.Thread):
        def run(self):
            global CAPACITY, buffer, in_index, out_index
            global mutex, empty, full
            items_produced = 0
            counter = 0
            while items_produced < 20:
                empty.acquire()
                mutex.acquire()
                counter += 1
                buffer[in_index] = counter
                in_index = (in_index + 1) % CAPACITY
                print("Producer produced : ", counter)
                mutex.release()
                full.release()
                time.sleep(1)
                items_produced += 1

    # Consumer Thread Class

    class Consumer(threading.Thread):
        def run(self):

            global CAPACITY, buffer, in_index, out_index, counter
            global mutex, empty, full

            items_consumed = 0

            while items_consumed < 20:
                full.acquire()
                mutex.acquire()

                item = buffer[out_index]
                out_index = (out_index + 1) % CAPACITY
                print("Consumer consumed item : ", item)

                mutex.release()
                empty.release()

                time.sleep(2.5)

                items_consumed += 1

    # Creating Threads
    producer = Producer()
    consumer = Consumer()

    # Starting Threads
    consumer.start()
    producer.start()

    # Waiting for threads to complete
    producer.join()
    consumer.join()

elif choice==3:
    # Define the maximum number of jobs that can be queued
    MAX_JOBS = 5

    # Define the shared job queue
    job_queue = []
    # Define a semaphore for controlling access to the job queue
    job_queue_mutex = threading.Semaphore(1)
    # Define a semaphore for indicating that the job queue is not empty
    job_queue_not_empty = threading.Semaphore(0)
    # Define a semaphore for indicating that the job queue is not full
    job_queue_not_full = threading.Semaphore(MAX_JOBS)

    # Define the printer thread function


    def printer_thread():
        while True:
            # Acquire the job queue not empty semaphore to wait for a job to be added to the queue
            job_queue_not_empty.acquire()
            # Acquire the job queue mutex to remove a job from the queue
            job_queue_mutex.acquire()
            # Remove the first job from the queue
            job = job_queue.pop(0)
            # Release the job queue mutex
            job_queue_mutex.release()
            # Release the job queue not full semaphore to signal that there is now room for another job
            job_queue_not_full.release()

            # Print the job
            print(f"Printing job {job}")
            time.sleep(1)  # Simulate the time it takes to print the job

    # Define the user thread function
    def user_thread():
        global job_queue
        # Generate a job ID (in this case, the current time as an integer)
        job_id = random.randint(1, 50)
        # Acquire the job queue not full semaphore to wait for space to add the job to the queue
        job_queue_not_full.acquire()
        # Acquire the job queue mutex to add the job to the queue
        job_queue_mutex.acquire()
        # Add the job ID to the end of the queue
        job_queue.append(job_id)
        # Release the job queue mutex
        job_queue_mutex.release()
        # Release the job queue not empty semaphore to signal that there is now a job in the queue
        job_queue_not_empty.release()

        print(f"Added job {job_id} to the queue.")
    # Create a printer thread and start it
    printer = threading.Thread(target=printer_thread, name="Printer")
    printer.start()

    # Create some user threads to add jobs to the queue
    for i in range(10):
        threading.Thread(target=user_thread, name=f"User {i+1}").start()
