# MPI (C/C++)

## Why move past pure-MPI programs?

MPI is an excellent tool for parallel execution of programs. A key strength is that the programmer must explicitly move data to where it is needed. That can make code easier to understand, albeit more work since both authors and maintainers spend more time reading existing code than writing new code, that is often desirable.</br>

However, such approaches tend to perform poorly at scale. Computer hardware has not grown much faster in the last 20 years, but instead made many more potentially parallel execution units available. One can hardly buy a single-core CPU any more, and HPC nodes with multiple CPU sockets each containing scores of cores abound. MPI was designed in an era where it was much more common to find a node with only a single processor and a single core, and total counts were in the hundreds to thousands. Such jobs are often too small to be permitted to run on current high-end clusters.
</br>

Code that assumes one MPI process to a core has trouble scaling to ```N``` processes (eg. for ```N > 1000```) for several reasons:

- collective communication cost tends to scale at least like aggregating messages helps a lot but more processes as starting and ending points for messages simply must take more time

- data must be replicated to each process, which takes time that grows with the process count

- replicated data forces cores to share the memory bandwith, thus defeating the advantages of shared memory caches

![image](https://user-images.githubusercontent.com/100533325/222922334-d4cf4a9f-f5ec-481c-b935-70416ad92026.png)

Imagine if a halo-exchange application like that from an earlier lesson was implemented in these two ways. The pure-MPI solution has a much larger volume of data in the border and halo regions. That means more data must be sent in total, as well as more messages between pairs of MPI ranks. In the hybrid case, both are reduced. However, the hybrid solution can have other challenges, including code complexity, usage complexity, synchronization, and avoiding problematic sharing.
</br>

## MPI + threading

The MPI standard has been updated to accommodate the use of threads within processes. Using these capabilities is optional, and presents numerous advantages and disadvantages

## Advantages of MPI + threading

- possiblity for better scaling of communication costs

- either simpler and/or faster code that does not need to distribute as much data, because all threads in the process can share it already

- higher performance from using memory caches better

- reduced need to dedicate a rank solely to communication coordination in code using a manager-worker paradigm

## Disadvantages of MPI + threading

- implicitly shared data can be harder to reason about correctly (eg. race conditions)

- code now has to be correct MPI code and correct threaded code

- possibility of lower performance from cache contention, when one thread writes to memory that is very close to where another thread needs to read

- more code complexity

- might be merely shifting bottlenecks from one place to another (eg. opening and closing OpenMP thread regions)

- needs higher quality MPI implementations

- it can be awkward to use libraries that also use threading internally

- usage gets more complicated, as both ranks and threads have to be shepherded onto cores for maximum performance


## mpich2 installation (Linux)

```bash
sudo apt-get install build-essential

sudo apt update

sudo apt-get install g++ gfortran

cd /tmp

wget http://www.mpich.org/static/downloads/1.4.1/mpich2-1.4.1.tar.gz

tar xzvf mpich2-1.4.1.tar.gz  

cd mpich2-1.4.1/

./configure

make

sudo make install

```

## Run MPI Code

```bash
mpicc -o sum.bin ./sum.c

mpirun -np 5 ./sum.bin
```

### Useful Sites

- [Using MPI with C](https://curc.readthedocs.io/en/latest/programming/MPI-C.html)
- [Running Open MPI through a job script](https://usc-rc.github.io/tutorials/open-mpi)
- [MPI programs](https://people.math.sc.edu/Burkardt/c_src/mpi/mpi.html)
