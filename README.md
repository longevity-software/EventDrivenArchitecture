# Event Driven Architecture Test Bed.

## Overview
This project is a simple(ish) application to explore the features and functionality of an event driven architecture for use in an embedded microcontroller.

## Microcontroller
The hardware intended to be used with this project is the Atmega644P Microcontroller, clocked from an 8MHz oscillator.

## Architecture overview
The application is split into three distinct sections:

### Device specific code
- This code is what talks directly to the hardware registers.
- Files in this section are named starting with "Atmega644P" for this device.

### Hardware Abstraction code
- This code is the interface between the device specific code and the application code.
- Files in this section are named starting with "Hardware".

### Application code
- This code sits on top of the other layers and implements the functionality required by the software.
- Files in this section are named appropriate to their function, with no special starting sequence.
- This section is unit tested where I though it applicable.

## Unit tests
Unit tests are run using Ceedling unit testing framework.

## Event system
Initially Events just consist of an event id, each part of the application or Hardware abstraction code can raise events by calling EVTQ_PostEvent in the EventQueue module, and can process events by implementing an event processing function which must be called from the main for(EVER) loop.
