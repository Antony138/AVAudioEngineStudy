/*
    Copyright (C) 2015 Apple Inc. All Rights Reserved.
    See LICENSE.txt for this sample’s licensing information
    
    将AVAudioEngine等要创建的对象封装到AudioEngine这个类中,统一管理
    AVAudioEngine这个API主要有2种类型的对象:1,engine对象(AVAudioEngine); 2,node对象。
    node对象有三种具体类型:1,output/input node; 2,mixer node; 3,player node
 
    Abstract:
    AudioEngine is the main controller class that creates the following objects:
                    AVAudioEngine       *_engine;
                    AVAudioPlayerNode   *_marimbaPlayer;
                    AVAudioPlayerNode   *_drumPlayer;
                    AVAudioUnitDelay    *_delay;
                    AVAudioUnitReverb   *_reverb;
                    AVAudioPCMBuffer    *_marimbaLoopBuffer;
                    AVAudioPCMBuffer    *_drumLoopBuffer;
                    
                 It connects all the nodes, loads the buffers as well as controls the AVAudioEngine object itself.
*/

// @import 是iOS7的新关键字，用这个，使用苹果官方的框架时，就不需要手动添加框架了，只写这一句即可
@import Foundation;

// effect strip 1 - Marimba Player -> Delay -> Mixer
// effect strip 2 - Drum Player -> Reverb -> Mixer

// 利用委托/代理机制，通知其他类(这里是ViewController)以下三种情况: engine被打断; engine配置被改变; mixerOutputFilePlayer被停止
// 即其他类(这里是ViewController)遵守了这个协议，即可以获得相关通知(和通告机制类似)
@protocol AudioEngineDelegate <NSObject>

@optional
- (void)engineWasInterrupted;
- (void)engineConfigurationHasChanged;
- (void)mixerOutputFilePlayerHasStopped;

@end

@interface AudioEngine : NSObject

// marimba(马林巴琴,一种音乐)以及drum(鼓)是否在播放
@property (nonatomic, readonly) BOOL marimbaPlayerIsPlaying;
@property (nonatomic, readonly) BOOL drumPlayerIsPlaying;

// 音量
@property (nonatomic) float marimbaPlayerVolume;    // 0.0 - 1.0
@property (nonatomic) float drumPlayerVolume;       // 0.0 - 1.0

// 这是什么?
@property (nonatomic) float marimbaPlayerPan;       // -1.0 - 1.0
@property (nonatomic) float drumPlayerPan;          // -1.0 - 1.0

// 音效?
@property (nonatomic) float delayWetDryMix;         // 0.0 - 1.0
@property (nonatomic) BOOL bypassDelay;

@property (nonatomic) float reverbWetDryMix;        // 0.0 - 1.0
@property (nonatomic) BOOL bypassReverb;

@property (nonatomic) float outputVolume;           // 0.0 - 1.0

@property (weak) id<AudioEngineDelegate> delegate;


// 播放Marimba(在控制器类中，调用本类.h文件以下方法)(这其实就是将"逻辑部分"和"界面"分离的一种方法)
- (void)toggleMarimba;
// 播放Drums
- (void)toggleDrums;

- (void)startRecordingMixerOutput;
- (void)stopRecordingMixerOutput;
- (void)playRecordedFile;
- (void)pausePlayingRecordedFile;
- (void)stopPlayingRecordedFile;

@end
