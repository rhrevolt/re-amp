/**
 *  SoundManager.h
 *
 *  Original Code : Van Stokes, Jr. (http://www.EvilMasterMindsInc.com) - Aug 05
 *  Modified Code : Steven Gay - mec3@bluewin.ch - Septembre 2005 - Jan 06
 */

#ifndef __SOUNDMANAGER_H__
#define __SOUNDMANAGER_H__

#include <stdio.h>
#include <string>

#include <al.h>
#include <alc.h>
#include <alut.h>

#include <boost/algorithm/string/trim.hpp>
#include <boost/foreach.hpp>

#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include "components/SoundComponent.h"

#define MAX_AUDIO_BUFFERS   64
#define MAX_AUDIO_SOURCES   16
#define MAX_FILENAME_LENGTH 40

class SoundManager
{
	private:
		bool isInitialised;
		ALCdevice* mSoundDevice;
		ALCcontext* mSoundContext;

		std::string mAudioPath;

		bool isSoundOn;

		ALfloat position[3];
		ALfloat velocity[3];
		ALfloat orientation[6];

		// Needed because of hardware limitation
		// Audio sources
		unsigned int mAudioSourcesInUseCount;
		unsigned int mAudioSources[ MAX_AUDIO_SOURCES ];
		bool         mAudioSourceInUse[ MAX_AUDIO_SOURCES ];

		// Audio buffers
		unsigned int mAudioBuffersInUseCount;
		unsigned int mAudioBuffers[ MAX_AUDIO_BUFFERS ];
		bool         mAudioBufferInUse[ MAX_AUDIO_BUFFERS ];
		char         mAudioBufferFileName[ MAX_AUDIO_BUFFERS ][ MAX_FILENAME_LENGTH ];

		// Function to check if the soundFile is already loaded into a buffer
		int locateAudioBuffer( std::string filename );
		int loadAudioInToSystem( std::string filename );
		bool loadWAV( std::string filename, ALuint pDestAudioBuffer );
		bool loadOGG( std::string filename, ALuint pDestAudioBuffer );
		// TODO bool loadAU( std::string filename, ALuint pDestAudioBuffer );

		// Ogg Vorbis extension
		bool bOggExtensionPresent;

		std::list<SoundComponent*> componentList;

	public:
		static SoundManager* mSoundManager;

		void tick(FrameData &fd);

		SoundManager( void );
		virtual ~SoundManager( void );
		void selfDestruct( void );
		static SoundManager* getManager( void );
		static SoundManager* getSingletonPtr( void ) { return mSoundManager; };
		int registerComponent(SoundComponent* pSoundComponent);
		int unregisterComponent(SoundComponent* pSoundComponent);

		bool init( void );
		bool getIsSoundOn( void ) { return isSoundOn; };
		void setAudioPath( char* path ) { mAudioPath = std::string( path ); };

		bool checkALError( void );
		bool checkALError( std::string pMsg );

		/** See http://www.openal.org/windows_enumeration.html for installing other
		 *   devices. You should at least have "Generic Hardware".
		 */
		std::string listAvailableDevices( void );

		// careful : testSound should not be used it doesn't use the resource limitation
		void testSound( const char* wavFile );

		// Aquire an Audio Source
		// filename = pass in the sound file to play for this source (ex. "myfile.wav")
		// audioId   = returns the AudioSource identifier you will need for the PlayAudioSource();
		bool loadAudio( std::string filename, unsigned int *audioId, bool loop );
		bool releaseAudio( unsigned int audioID );

		// deprecated
		bool aquireAudioSource( char* file, unsigned int *audioId )
		{ return loadAudio( std::string(file), audioId, false ); };

		// Returns true if the audio is started from the beginning
		// false if error or if already playing
		bool playAudio( unsigned int audioId, bool forceRestart );
		bool stopAudio( unsigned int audioID );
		bool stopAllAudio( void );

		bool pauseAudio( unsigned int audioID );
		bool pauseAllAudio( void );
		bool resumeAudio( unsigned int audioID );
		bool resumeAllAudio( void );

		bool setSoundPosition( unsigned int audioID, Ogre::Vector3 position );

		bool setSoundPosition( unsigned int audioID, Ogre::Vector3 position,
				Ogre::Vector3 velocity, Ogre::Vector3 direction );

		bool setSound( unsigned int audioID, Ogre::Vector3 position,
				Ogre::Vector3 velocity, Ogre::Vector3 direction, float maxDistance,
				bool playNow, bool forceRestart, float minGain );

		bool setListenerPosition( Ogre::Vector3 position, Ogre::Vector3 velocity,
				Ogre::Quaternion orientation );

		bool isOggExtensionPresent( void );
};

#endif /*__SOUNDMANAGER_H__*/
