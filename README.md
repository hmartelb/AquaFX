# AquaFX

> This project integrates the Kinect sensor with PureData via OSC protocol to recreate a 3D Sound experience that can be controlled using full-body interaction. 

## Introduction

The interactive experience is based on a swimming competition. The composition covers the whole process of participating in the event, from entering the changing rooms of the compound to the victory ceremony, focusing on the race itself.

We mainly used sounds of water, but also from the crowd and the other elements that are usually present in this kind of events. Panning techniques will be used to create a 3D sensation, and filtering/EQ is going to be used to simulate the subaquatic sound that cannot be recorded with conventional handhold recorders. The main goal is to make the listener feel like the competitor so that it can virtually be inside the environment.

## Getting started
Download the repository and make sure to set up the following environments:

- Visual Studio Community 2017 or greater: https://visualstudio.microsoft.com/en/downloads/
- Openframeworks extension for Visual Studio: https://openframeworks.cc/setup/vs/
- Kinect for Windows SDK: https://developer.microsoft.com/en-us/windows/kinect
- PureData environment: https://puredata.info/

After the setup, you will need to perform these steps:

1) Connect the Kinect sensor to the computer
2) Open the PD patch "OSCKinectBasic_concert.pd"
3) Open the OF Application "kinectBase.exe"

Now you are ready to start playing!

> WARNING: Provided the list of dependencies, the project can only be executed in a Windows OS. Using alternative packages may cause the application to have unexpected behavior.

## Usage

Inside the PureData patch, click on the button labeled "Start". The initial sequence will play up to the point when the swimming race will start. In that moment, a start whistle will be heard.

The race starts when the user raises both arms above the head to dive into the water. Then the dive and underwater can be heard, and in a few seconds the user can start swimming. Each stroke is counted by the Kinect sensor as the velocity of each of the arms, and a minimum of 70 strokes have to be made in order to win the race (100 m freestyle).

## Further reading

Please check out the project's blog, where we explained all the steps involved in obtaining the recordings and the application development: 

https://aquafxblog.wordpress.com/

## License

This project is licensed under the MIT License.
```
MIT License

Copyright (c) 2016 The AquaFX Team
Héctor Martel, Ferran Morata

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
