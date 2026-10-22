> this programme calculates the opposition to alternating current in different circuit components by using a single function call
it is useful for analysing AC circuits containing several types of components that need to be proccessed through a common interface
One base-class pointer (Component*) can point to any of the three component types.
The call parts[i]->impedance(f) is written once, but C++ picks the correct version at runtime based on the actual object and this is what virtual does.
A new component, such as a diode or a transformer, can be added without changing the loop 
![alt text](20261022_124617-1.jpg)