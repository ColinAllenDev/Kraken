# Event System
---

## Application
The centeral class of our engine that handles running and receiving events as well as propegating them to layers. Contains an event 'listener'.

## Window
A representation of our application window. When an event occurs in our window, the window class will receive an event callback, it must then construct a KrakenEvent and then propogate it back to our Application.

## Event
Represents information about events that have occured. 

## IEventListener
The event listener interface.