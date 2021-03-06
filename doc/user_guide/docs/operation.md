# Operation

Operations are functions that are executed for each simulation object.
To execute a function for *specific* simulation objects have a look at
biology modules.

To support multiscale simulations, operations have a data member frequency.
If it is set to one it means that this function will be executed for every
time step. If this member is set to two it will be executed every second time
step, and so on.

Here the link for the complete API documentation for [Operation](https://biodynamo.github.io/api/structbdm_1_1Operation.html)

## Usage examples

### Add a user-defined operation

Below you can find a code example to add an operation that prints all
simulation object unique ids.

``` C++
auto* scheduler = simulation.GetScheduler();
Operation op("print uid op", [](SimObject* so){
    std::cout << "SimObject " << so->GetUid() << std::endl;
});
scheduler->AddOperation(op);
```

### Change the execution frequency of an operation

Let's assume that we want to output all unique ids every 100 timesteps instead
of every.

``` C++
auto* scheduler = simulation.GetScheduler();
scheduler->GetOperation("print uid op")->frequency_ = 100;
```
