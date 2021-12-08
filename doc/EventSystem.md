# Event System
---
The event system in the Kraken Engine is one of the most important systems in this project. 

## Application
The centeral class of our engine that handles receiving and dispatching events as well as propegating them to [Layers]().

## Window
A representation of our application window. When an event occurs in our window, the window class will receive an event callback, it must then construct a KrakenEvent and then propogate it back to our Application.

## Event
The core event handler class. Defines event types, categories as well as functionality for recieving information about events and dispatching them.

>Note: currently these events could be considered 'blocking events' (they are processed as they occur), in the future events will be buffered in an Event Bus and will be processed during the 'event' part of the update stage.


