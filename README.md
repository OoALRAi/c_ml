## neural network in c
 a very simple implementation from scratch where no third party library has been used.
 it includes a very simple matrix library to enable matrix multiplication for forward pass and backward pass

### NOTE:
    the implementation is not memory safe and leaks too much memory!!

### usage:
* first example learns to square numbers
```bash
make nn_square
```
* note that this model learn to square a given number in range of values that it has been trained on.
* for greater ranges the model may explode during training phase!

### TODOS:
* implement sigmoid (DONE)
* test sigmoid
* implement softmax
* solve mnist recognition using FFNN only
