>The program is intended helps to the user determine  whether a cable of a particular length and thickness can cause excessive voltage drop or waste too much electrical energy in form of heat

A Cable object can access functions from all three levels of the inheritance hierarcy; that is: displayMaterial() from the grandparent, resistance() from the parent, and powerLoss() from itself.
Constructors are executed inorder from the highest level to the lowest level; material,then wire and finally cable
this approach allows code to be reused acrosss the classes instead of writing the same code repeatedly

**Below is the diagram for the polymophism block**

![alt text](20261022_124600-1.jpg)