#pragma once
#include <LabSound/extended/LabSound.h>

#include <map>
#include <memory>
#include <string>

class SoundManager {
 public:
  explicit SoundManager();

  void LoadClip(const std::string& filename);
  void Play(const std::string& filename);
  void SetVolume(float volume) { _gain->gain()->setValue(volume); }

  void Mute();
  void UnMute() {
    SetVolume(_previousVolume);
    _muted = false;
  }

  bool IsMuted() const { return _muted; }

 private:
  std::unique_ptr<lab::AudioContext> _context;
  std::map<std::string, std::shared_ptr<lab::AudioBus>> _files;
  std::map<std::string, std::shared_ptr<lab::SampledAudioNode>> _samples;
  std::shared_ptr<lab::GainNode> _gain;
  float _previousVolume;
  bool _muted;
};