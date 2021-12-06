# JustAudioFX - DSP Algorithms
Collection of audio FX plugins with algorithms explained, using Juce Framework. 

## Requirements
* JUCE and Projucer v6 (https://juce.com/get-juce/download)
* C++ IDE

## Current list of digital audio FX algorithms:
* [Stereo Delay](./JustDelay)

![image](https://user-images.githubusercontent.com/6858921/142690302-c4676b8d-21e7-465e-bd95-13e96b29ef23.png)

* [Ping-Pong Delay](./JustPingPongDelay)

![image](https://user-images.githubusercontent.com/6858921/142690396-4f2484bc-35c3-406b-8652-deebe5cb1414.png)

## How to install compiled VST plugin?
All ready-to-use plugins are available in the [Releases](https://github.com/TheAvalanche/JustAudioFX/releases) page. 
* Download the \*.vst3 files
* Put the downloaded files into your default VST3 location (usually in `C:\Program Files\Common Files\VST3` on Windows)

## How to run and debug?
!!! DISCLAIMER !!!

Currently here are instructions only for Visual Studio 2019 and VST3. Feel free to add for other IDEs. 

* Setup Projucer (TODO: add instructions)
* Build AudioPluginHost and capture path to executable (${JUCE_PATH}\extras\AudioPluginHost\Builds\VisualStudio2019\x64\Debug\App\AudioPluginHost.exe) (TODO: add instructions)
* Clone the project
* In Projucer choose File -> Open... and select `*.jucer` file from the folder, that you want to launch
* In Projucer choose File -> Save Project and Open in IDE...
* In Visual Studio choose XXX_VST3 solution and set as Startup Project
* In Visual Studio select Debug -> XXX_VST3 Debug Properties
* In Configuration Properties -> Debugging put path to AudioPluginHost.exe
* In Visual Studio select Debug -> Start Debugging
* Configure AudioPluginHost to add your vst3 plugin and save graph (TODO: add instructions)
