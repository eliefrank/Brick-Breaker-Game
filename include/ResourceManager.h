#pragma once
#include <unordered_map>
#include <string>
#include "Macros.h"
#include <SFML/Audio.hpp>

class ResourceManager
{
public:
	static ResourceManager& instance();
	sf::Texture* getTexture(const Type);
	PhysicsInfo getPhysicsInfo(const Type t);
	const sf::Font& getFont();

	void setSong(const Sound);
	void playSFXball();
	void playSFXbullet();
	void playSFXlost();
	void playSFXnextLevel();
	void playSFXbonus();

private:
	ResourceManager();
	void loadTexture(const std::string, const Type);
	void loadSound(const std::string path, const Sound name);

	void playSong();
	void stopAllSongs();
	void setVolume();

	std::unordered_map<Type, sf::Texture> m_textures;
	sf::Font m_font;

	std::unordered_map<Sound, sf::SoundBuffer> m_soundBuff;
	std::vector <sf::Sound> m_sounds;
	Sound m_playing = Sound::Menu;
};
