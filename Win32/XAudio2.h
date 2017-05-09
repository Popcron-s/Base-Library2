#pragma once

#include "..\\Interface\\Base_Output_Sounds.h"
#include "..\\Common\\Enum.h"
#include "..\\Common\\List.h"

#include <XAudio2.h>

#pragma comment(lib, "XAudio2.lib")

class XAudio2 : public _O_Sounds{
private:
	IXAudio2* m_pEngine;
	IXAudio2MasteringVoice* m_pMaster;
	struct _node{
		IXAudio2SourceVoice* source;
		XAUDIO2_BUFFER buffer;
	};
	List<_node> m_SourceList;
	//SOUND s;
	//WAVEFORMATEX format;

	//listener

	XAudio2() : m_pEngine(nullptr), m_pMaster(nullptr){}

public:
	static _O_Sounds* GetSingleton(){
		if(m_pSingleton == nullptr){
			m_pSingleton = new XAudio2;
		}
		return m_pSingleton;
	}

	_INTERFACE::SOUND GetType(){return _INTERFACE::SOUND::XAudio2;};

	bool Init(){
		//CoInitializeEx( NULL, COINIT_MULTITHREADED );
		XAudio2Create(&m_pEngine, 0, XAUDIO2_DEFAULT_PROCESSOR);
		m_pEngine->CreateMasteringVoice(&m_pMaster);

		return true;
	}
	bool RegistGraph(SOUND s, UINT loop = 0){
		WAVEFORMATEX format;
		format.wFormatTag		= s.wFormatTag;		
		format.nChannels		= s.nChannels;		
		format.wBitsPerSample	= s.wBitsPerSample;	
		format.nSamplesPerSec	= s.nSamplesPerSec;	
		format.nBlockAlign		= s.nBlockAlign;		
		format.nAvgBytesPerSec	= s.nAvgBytesPerSec;	
		format.cbSize			= s.cbSize;			
		
		_node t_node = {nullptr, {}};
		t_node.buffer = {};
		t_node.buffer.pAudioData = s.buf;
		t_node.buffer.AudioBytes = s.size;
		t_node.buffer.PlayBegin = 0;
		t_node.buffer.PlayLength = 0;
		t_node.buffer.LoopBegin = 0;
		t_node.buffer.LoopLength = 0;
		t_node.buffer.LoopCount = loop;
		t_node.buffer.Flags = XAUDIO2_END_OF_STREAM;

		m_pEngine->CreateSourceVoice(&(t_node.source), &format);

		t_node.source->Start();
		t_node.source->SubmitSourceBuffer(&(t_node.buffer));
		//g_source->SetVolume(1.0f);

		m_SourceList.CreateNode(t_node);

		return true;
	}
	bool RemoveGraph(UINT id){
		m_SourceList.ReleaseNode(id);

		return true;
	}
	bool Release(){
		m_pEngine->Release();
		//CoUninitialize();

		return true;
	}

	void Run(){
		List<_node>::iterator iter = m_SourceList.Begin();
		for(INT i = 0 ; iter != m_SourceList.End() ; ++iter, ++i){
			XAUDIO2_VOICE_STATE state = {};
			iter->source->GetState(&state);
			if(state.BuffersQueued == 0){m_SourceList.ReleaseNode(i); --i;}
		}
	}
};