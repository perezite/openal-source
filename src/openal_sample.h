#ifndef __OPENAL_SAMPLE_H
#define __OPENAL_SAMPLE_H

#include "AL/al.h"
#include "KeyValues.h"

#define NUM_BUFFERS 4
#define BUFFER_SIZE 65536 // 65536 bytes = 64KB

class IOpenALSample
{
public:
	IOpenALSample();
	virtual ~IOpenALSample();

	void Init();
	void Destroy();

	void Update(const float lastUpdate);
	inline void UpdateBuffers(const float lastUpdate);
	inline void UpdatePositional(const float lastUpdate);

	void Play();
	void Stop();
	void Pause();

	bool IsPlaying();
	bool IsReady();
	bool IsFinished();
	bool IsPositional();

	void LinkEntity(CBaseEntity* ent);
	void UnlinkEntity();

	void SetPositional(bool positional);
	void SetPosition(float x, float y, float z);
	void SetPosition(Vector position);
	void SetPosition(const float position[3]);
	void SetVelocity(const float orientation[3]);
	void SetVelocity(const Vector velocity);

	void SetLooping(bool shouldLoop);
	void ClearBuffers();

	void BufferData(ALuint bid, ALenum format, const ALvoid* data, ALsizei size, ALsizei freq);

	// Methods specific formats use to fully support/define the sample
	virtual bool InitFormat() { return true; };
	virtual void DestroyFormat() {};

	virtual void Open(const char* filename) { Init(); };
	virtual void Close() { };

	virtual bool CheckStream(ALuint buffer) { return true; };

	virtual void UpdateMetadata() {};
	void ClearMetadata() { metadata->Clear(); };

protected:
	bool m_bStreaming; // Are we in streaming mode, or should we preload the data?
	bool m_bFinished;  // Are we finished playing this sound? Can we delete this?
	bool m_bLooping;   // Is this sample in a constant looping state?
	bool m_bReady;     // Are we ready to play this file?
	bool m_bRequiresSync; // If this is true, we syncronize with the engine.
	bool m_bPositional; // Are we placed in a world position?

	CBaseEntity* m_pLinkedEntity; // Used for linking entities to this sample's source

	float m_fPosition[3]; // Where is this sample source?
	float m_fVelocity[3]; // In which velocity is our source playing?
	float m_fGain; // This is the gain of our sound
	float m_fFadeScalar; // The gain of our sound is multiplied by this

	KeyValues* metadata; // Metadata about the audio

	ALuint buffers[NUM_BUFFERS];  // Buffers to queue our data into
	ALuint source;                // Our source's identifier for OpenAL
	ALenum format;                // A simple OpenAL-usable format description
};

#endif
