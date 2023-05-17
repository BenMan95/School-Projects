# Part B - Queue

This part assumes you already have knowledge of Google Tests and how to write unit tests. If you 
don't, you should do part A first.

This part will be similar to part A with a couple of key differences:
* You are not given the implementation file, only the header file
* There are a lot more mutants
* Hints are a little more vague and less helpful

### Provided Files

For this part, we have not provided the actual `queue.cc` file, but we have provided `queue.h` (it's in 
the `include` folder).  Use `queue.h` to figure out functions of the Queue class are and how
they should be called.

Additionally, we have provided `queue.o`, a compiled version of `queue.cc` that 
you can use to locally run your programs. You may assume that `queue.o` is the correct version of the 
code.

We have also provided a template `main.cc` file that shows example usage of the Queue class. Feel free 
to edit this file as much as you want (you won't be submitting it anyways). You can compile and 
run the code you write in `main.cc` with:

(*code templates assume you are in the current directory*)
```
make

./queue
```
Use the `main.cc` file to clarify any questions or confusions about the expected behavior of the
Queue class.

Finally, we have provided a template `queue_unittest.cc` file. You will have to fill this file out 
with your own unit tests and submit it to Gradescope. At any time, you can run your tests against the 
correct version of the code with:
```
make

./queue_unittest
```
Since it is being run against the *correct* version of the code, all of your tests should *pass*. If 
your tests do not *pass* when you run it locally, then that means that your tests are not correctly using
the Queue class. Again, you can use the `main.cc` file to understand how to correctly use the class and 
test stuff out there.

## **Submission**

Submit your work by uploading the `queue_unittest.cc` file to Gradescope. You can upload as many times 
as you want until the deadline. Note that if your tests do not *pass* against the *correct* version of 
the code (which you can test locally), you will not receive any points for catching the mutants.

### Notes

* Ensure that the file you submit is named exactly `queue_unittest.cc`, otherwise the autograder will not use your file and instead use the empty template file.
