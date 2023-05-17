#include "gtest/gtest.h"
#include "queue.h"


class QueueTest : public ::testing::Test {
 public:
  void SetUp( ) { 
    zero     = Queue(0);
    one      = Queue(1);
    unsorted = Queue(20);
    sorted   = Queue(20);
    filled   = Queue(10);

    one.enqueue(0);

    for (int i = 0; i < 5; i ++) {
      filled.enqueue(0);
      filled.dequeue();
    }

    for (int i = 0; i < 10; i++) {
      unsorted.enqueue(nums[i]);
      sorted.enqueue(snums[i]);
      filled.enqueue(nums[i]);
    }
  }
 protected:
  int nums[10]  = {-3,-6,0,5,3,-5,-4,-1,2,6};
  int snums[10] = {-6,-5,-4,-3,-1,0,2,3,5,6};

  Queue zero;
  Queue one;
  Queue unsorted;
  Queue sorted;
  Queue filled;

  testing::ExitedWithCode failure = testing::ExitedWithCode(EXIT_FAILURE);
};

TEST_F(QueueTest, QueueDefaultConstructorTest) {
  Queue defcon;
  EXPECT_EXIT(defcon.peek(), failure, "") << "Default constructor does not initialize correctly";
  EXPECT_EQ(defcon.size(),        0)      << "Default constructor does not initialize correctly";
  EXPECT_EQ(defcon.isEmpty(),     true)   << "Default constructor does not initialize correctly";
  EXPECT_EQ(defcon.isFull(),      false)  << "Default constructor does not initialize correctly";
  EXPECT_EQ(defcon.getCapacity(), SIZE)   << "Default constructor does not initialize correctly";
}

TEST_F(QueueTest, QueueCopyConstructorsTest) {
  Queue copy = unsorted;

  EXPECT_EQ(unsorted.peek(),        copy.peek())        << "Queue not copied correctly";
  EXPECT_EQ(unsorted.size(),        copy.size())        << "Queue not copied correctly";
  EXPECT_EQ(unsorted.isEmpty(),     copy.isEmpty())     << "Queue not copied correctly";
  EXPECT_EQ(unsorted.isFull(),      copy.isFull())      << "Queue not copied correctly";
  EXPECT_EQ(unsorted.getCapacity(), copy.getCapacity()) << "Queue not copied correctly";

  Queue assign;
  assign = unsorted;

  EXPECT_EQ(unsorted.peek(),        assign.peek())        << "Queue not assigned correctly";
  EXPECT_EQ(unsorted.size(),        assign.size())        << "Queue not assigned correctly";
  EXPECT_EQ(unsorted.isEmpty(),     assign.isEmpty())     << "Queue not assigned correctly";
  EXPECT_EQ(unsorted.isFull(),      assign.isFull())      << "Queue not assigned correctly";
  EXPECT_EQ(unsorted.getCapacity(), assign.getCapacity()) << "Queue not assigned correctly";

  for (int i = -10; i <= 10; i++) {
    int index = unsorted.indexOf(i);
    EXPECT_EQ(index, copy.indexOf(i)) << "Queue not copied correctly";
    EXPECT_EQ(index, assign.indexOf(i)) << "Queue not assigned correctly";
  }

  for (int i = 0; i < 10; i++) {
    int dequeued = unsorted.dequeue();

    EXPECT_EQ(dequeued,               copy.peek())        << "Queue not copied correctly";
    EXPECT_EQ(dequeued,               copy.dequeue())     << "Queue not copied correctly";
    EXPECT_EQ(unsorted.size(),        copy.size())        << "Queue not copied correctly";
    EXPECT_EQ(unsorted.isEmpty(),     copy.isEmpty())     << "Queue not copied correctly";
    EXPECT_EQ(unsorted.isFull(),      copy.isFull())      << "Queue not copied correctly";
    EXPECT_EQ(unsorted.getCapacity(), copy.getCapacity()) << "Queue not copied correctly";

    EXPECT_EQ(dequeued,               assign.peek())        << "Queue not assigned correctly";
    EXPECT_EQ(dequeued,               assign.dequeue())     << "Queue not assigned correctly";
    EXPECT_EQ(unsorted.size(),        assign.size())        << "Queue not assigned correctly";
    EXPECT_EQ(unsorted.isEmpty(),     assign.isEmpty())     << "Queue not assigned correctly";
    EXPECT_EQ(unsorted.isFull(),      assign.isFull())      << "Queue not assigned correctly";
    EXPECT_EQ(unsorted.getCapacity(), assign.getCapacity()) << "Queue not assigned correctly";
  }

  EXPECT_EXIT(copy.peek(),    failure, "")   << "Queue not copied correctly";
  EXPECT_EXIT(copy.dequeue(), failure, "")   << "Queue not copied correctly";
  EXPECT_EXIT(assign.peek(),    failure, "") << "Queue not assigned correctly";
  EXPECT_EXIT(assign.dequeue(), failure, "") << "Queue not assigned correctly";
  
  unsorted.enqueue(1);
  for (int i = 0; i < 20; i++) {
    copy.enqueue(0);
    assign.enqueue(0);
  }
  EXPECT_EQ(unsorted.peek(), 1) << "Shallow copy performed instead of deep copy";
}

TEST_F(QueueTest, QueueDequeueTest) {
  EXPECT_EXIT(zero.dequeue(), failure, "") << "Did not exit on dequeue from empty";

  EXPECT_EQ(one.dequeue(), 0)             << "Value not dequeued correctly";
  EXPECT_EXIT(one.dequeue(), failure, "") << "Did not exit on dequeue from empty";

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.dequeue(), nums[i])  << "Value not dequeued correctly";
    EXPECT_EQ(sorted.dequeue(),   snums[i]) << "Value not dequeued correctly";
  }

  EXPECT_EXIT(unsorted.dequeue(), failure, "") << "Did not exit on dequeue from empty";
  EXPECT_EXIT(sorted.dequeue(),   failure, "") << "Did not exit on dequeue from empty";
}

TEST_F(QueueTest, QueuePeekTest) {
  EXPECT_EXIT(zero.peek(), failure, "") << "Did not exit on peek on empty";

  EXPECT_EQ(one.peek(), 0) << "Returned incorrect value from peek";
  one.dequeue();
  EXPECT_EXIT(one.peek(), failure, "") << "Did not exit on peek on empty";

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.peek(), nums[i])  << "Returned incorrect value from peek";
    EXPECT_EQ(sorted.peek(),   snums[i]) << "Returned incorrect value from peek";
    unsorted.dequeue();
    sorted.dequeue();
  }
}

TEST_F(QueueTest, QueueEnqueueTest) {
  EXPECT_EXIT(zero.enqueue(0), failure, "") << "Did not exit on enqueue to full";

  EXPECT_EXIT(one.enqueue(0),  failure, "") << "Did not exit on enqueue to full";
  one.dequeue();
  one.enqueue(9);
  EXPECT_EXIT(one.enqueue(0),  failure, "") << "Did not exit on enqueue to full";
  EXPECT_EQ(one.peek(),9)                   << "Value not enqueued correctly";
  EXPECT_EQ(one.dequeue(),9)                << "Value not enqueued correctly";

  for (int i = 0; i < 10; i++) {
    unsorted.dequeue();
    unsorted.enqueue(nums[i]);
    sorted.enqueue(snums[i]);
  }

  for (int i = 0; i < 10; i++)
    sorted.dequeue();
    
  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.dequeue(), nums[i])  << "Value not enqueued correctly";
    EXPECT_EQ(sorted.dequeue(),   snums[i]) << "Value not enqueued correctly";
  }
}

TEST_F(QueueTest, QueueIndexOfTest) {
  EXPECT_EQ(zero.indexOf(1), -1) << "Failed to return -1 as index of nonexistent element";
  EXPECT_EQ(one.indexOf(1), -1)  << "Failed to return -1 as index of nonexistent element";
  EXPECT_EQ(one.indexOf(0), 0)   << "Failed to return correct index";

  filled.bubbleSort();

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.indexOf(nums[i]), i) << "Failed to return correct index";
    EXPECT_EQ(sorted.indexOf(snums[i]),  i) << "Failed to return correct index";
    EXPECT_EQ(filled.indexOf(snums[i]),  i) << "Failed to return correct index";
  }

  int i = 0;
  for (int n = -10; n <= 10; n++) {
    if (i < 10 && n == snums[i]) {
      EXPECT_NE(unsorted.indexOf(n), -1) << "Returned -1 as index of existent element";
      EXPECT_NE(sorted.indexOf(n),   -1) << "Returned -1 as index of existent element";
      EXPECT_NE(filled.indexOf(n),   -1) << "Returned -1 as index of existent element";
      i++;
    } else {
      EXPECT_EQ(unsorted.indexOf(n), -1) << "Failed to return -1 as index of nonexistent element";
      EXPECT_EQ(sorted.indexOf(n),   -1) << "Failed to return -1 as index of nonexistent element";
      EXPECT_EQ(filled.indexOf(n),   -1) << "Failed to return -1 as index of nonexistent element";
    }
  }
}

TEST_F(QueueTest, QueueSizeTest) {
  EXPECT_EQ(zero.size(), 0)      << "Returned incorrect size for empty queue";
  EXPECT_EQ(one.size(), 1)       << "Returned incorrect size for one element queue";
  EXPECT_EQ(sorted.size(), 10)   << "Returned incorrect size for queue";
  EXPECT_EQ(unsorted.size(), 10) << "Returned incorrect size for queue";

  for (int i = 1; i <= 10; i++) {
    unsorted.dequeue();
    sorted.enqueue(0);
    EXPECT_EQ(unsorted.size(), 10 - i) << "Returned incorrect size for queue";
    EXPECT_EQ(sorted.size(),   10 + i) << "Returned incorrect size for queue";
  }
}

TEST_F(QueueTest, QueueIsEmptyTest) {
  EXPECT_EQ(zero.isEmpty(), true)  << "Did not return empty for empty list";
  EXPECT_EQ(one.isEmpty(),  false) << "Returned empty for non-empty list";
  one.dequeue();
  EXPECT_EQ(one.isEmpty(), true)      << "Did not return empty for empty list";

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.isEmpty(), false) << "Returned empty for non-empty list";
    EXPECT_EQ(sorted.isEmpty(),   false) << "Returned empty for non-empty list";
    unsorted.dequeue();
    sorted.dequeue();
  }

  EXPECT_EQ(unsorted.isEmpty(), true) << "Did not return empty for empty list";
  EXPECT_EQ(sorted.isEmpty(), true)   << "Did not return empty for empty list";
}

TEST_F(QueueTest, QueueIsFullTest) {
  EXPECT_EQ(zero.isFull(), true) << "Did not return full for full list";
  EXPECT_EQ(one.isFull(), true)  << "Did not return full for full list";
  one.dequeue();
  EXPECT_EQ(one.isFull(), false)  << "Returned full for non-full list";

  for (int i = 0; i < 10; i++) {
    EXPECT_EQ(unsorted.isFull(), false) << "Returned full for non-full list";
    EXPECT_EQ(sorted.isFull(),   false) << "Returned full for non-full list";
    unsorted.enqueue(0);
    sorted.enqueue(0);
  }

  EXPECT_EQ(unsorted.isFull(), true) << "Did not return full for full list";
  EXPECT_EQ(sorted.isFull(),   true) << "Did not return full for full list";
}

TEST_F(QueueTest, QueueGetCapacityTest) {
  Queue q;
  EXPECT_EQ(q.getCapacity(), SIZE)      << "Incorrect capacity returned";
  EXPECT_EQ(zero.getCapacity(), 0)      << "Incorrect capacity returned";
  EXPECT_EQ(one.getCapacity(), 1)       << "Incorrect capacity returned";
  EXPECT_EQ(unsorted.getCapacity(), 20) << "Incorrect capacity returned";
  EXPECT_EQ(sorted.getCapacity(), 20)   << "Incorrect capacity returned";
}

TEST_F(QueueTest, QueueClearTest) {
  zero.clear();
  EXPECT_EXIT(zero.peek(),    failure, "") << "Queue not cleared correctly";
  EXPECT_EXIT(zero.dequeue(), failure, "") << "Queue not cleared correctly";
  EXPECT_EQ(zero.size(),        0)         << "Queue not cleared correctly";
  EXPECT_EQ(zero.isEmpty(),     true)      << "Queue not cleared correctly";
  EXPECT_EQ(zero.isFull(),      true)      << "Queue not cleared correctly";
  EXPECT_EQ(zero.getCapacity(), 0)         << "Queue not cleared correctly";

  one.clear();
  EXPECT_EXIT(one.peek(),    failure, "") << "Queue not cleared correctly";
  EXPECT_EXIT(one.dequeue(), failure, "") << "Queue not cleared correctly";
  EXPECT_EQ(one.size(),        0)         << "Queue not cleared correctly";
  EXPECT_EQ(one.isEmpty(),     true)      << "Queue not cleared correctly";
  EXPECT_EQ(one.isFull(),      false)     << "Queue not cleared correctly";
  EXPECT_EQ(one.getCapacity(), 1)         << "Queue not cleared correctly";

  unsorted.clear();
  EXPECT_EXIT(unsorted.peek(),    failure, "") << "Queue not cleared correctly";
  EXPECT_EXIT(unsorted.dequeue(), failure, "") << "Queue not cleared correctly";
  EXPECT_EQ(unsorted.size(),        0)         << "Queue not cleared correctly";
  EXPECT_EQ(unsorted.isEmpty(),     true)      << "Queue not cleared correctly";
  EXPECT_EQ(unsorted.isFull(),      false)     << "Queue not cleared correctly";
  EXPECT_EQ(unsorted.getCapacity(), 20)        << "Queue not cleared correctly";

  sorted.clear();
  EXPECT_EXIT(sorted.peek(),    failure, "") << "Queue not cleared correctly";
  EXPECT_EXIT(sorted.dequeue(), failure, "") << "Queue not cleared correctly";
  EXPECT_EQ(sorted.size(),        0)         << "Queue not cleared correctly";
  EXPECT_EQ(sorted.isEmpty(),     true)      << "Queue not cleared correctly";
  EXPECT_EQ(sorted.isFull(),      false)     << "Queue not cleared correctly";
  EXPECT_EQ(sorted.getCapacity(), 20)        << "Queue not cleared correctly";
}

TEST_F(QueueTest, QueueBubbleSortTest) {
  unsorted.bubbleSort();
  filled.bubbleSort();

  EXPECT_EQ(unsorted.size(), sorted.size());
  EXPECT_EQ(filled.size(), sorted.size());
  
  for (int i = 0; i < 10; i++) {
    int expected = sorted.dequeue();
    EXPECT_EQ(unsorted.dequeue(), expected) << "Queue not sorted correctly with bubble sort";
    EXPECT_EQ(filled.dequeue(),   expected) << "Queue not sorted correctly with bubble sort";
  }
}

TEST_F(QueueTest, QueueMergeSortTest) {
  unsorted.mergeSort();
  filled.mergeSort();

  EXPECT_EQ(unsorted.size(), sorted.size());
  EXPECT_EQ(filled.size(), sorted.size());

  for (int i = 0; i < 10; i++) {
    int expected = sorted.dequeue();
    EXPECT_EQ(unsorted.dequeue(), expected) << "Queue not sorted correctly with merge sort";
    EXPECT_EQ(filled.dequeue(),   expected) << "Queue not sorted correctly with merge sort";
  }
}
