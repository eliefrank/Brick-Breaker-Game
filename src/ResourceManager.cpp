#include "ResourceManager.h"

void ResourceManager::setSong(const Sound song)
{
	m_playing = song;
	playSong();
}

void ResourceManager::playSFXball()
{
	m_sounds[(int)Sound::Ball].play();
}

void ResourceManager::playSFXbullet()
{
	if(m_sounds[(int)Sound::Bullet].getStatus() != sf::Sound::Status::Playing)
		m_sounds[(int)Sound::Bullet].play();
}

void ResourceManager::playSFXlost()
{
	m_sounds[(int)Sound::Lost].play();
}

void ResourceManager::playSFXnextLevel()
{
	m_sounds[(int)Sound::NextLevel].play();
}

void ResourceManager::playSFXbonus()
{
	m_sounds[(int)Sound::Bonus].play();
}

void ResourceManager::playSong()
{
	stopAllSongs();
	m_sounds[(int)m_playing].play();
}

void ResourceManager::stopAllSongs()
{
	for (auto& sound : m_sounds)
		sound.stop();
}

void ResourceManager::setVolume()
{
	m_sounds[(int)Sound::Menu].setVolume(20);
	m_sounds[(int)Sound::Game].setVolume(20);
	m_sounds[(int)Sound::Bullet].setVolume(50);
	m_sounds[(int)Sound::Ball].setVolume(50);
	m_sounds[(int)Sound::Bonus].setVolume(50);
	m_sounds[(int)Sound::NextLevel].setVolume(100);
	m_sounds[(int)Sound::Lost].setVolume(100);
}

void ResourceManager::loadSound(const std::string path, const Sound name)
{
	sf::SoundBuffer temp;
	temp.loadFromFile(path);
	m_soundBuff[name] = temp;
}

ResourceManager& ResourceManager::instance()
{
	static ResourceManager instance;
	return instance;
}

sf::Texture* ResourceManager::getTexture(const Type name)
{
	return &m_textures[name];
}

PhysicsInfo ResourceManager::getPhysicsInfo(const Type t)
{
	return pI[int(t)];
}

ResourceManager::ResourceManager()
{
	for (int i = 0; i < images.size(); i++)
		loadTexture(images[i], Type(i));

	m_font.loadFromFile("Bricks.ttf");

	for (int i = 0; i < sounds.size(); i++)
	{
		loadSound(sounds[i], Sound(i));
		m_sounds.push_back(sf::Sound(m_soundBuff[Sound(i)]));
	}
	
	setVolume();
	
	m_sounds[(int)Sound::Menu].setLoop(true);
	m_sounds[(int)Sound::Game].setLoop(true);
}

void ResourceManager::loadTexture(const std::string path, const Type name)
{
	sf::Texture temp;
	temp.loadFromFile(path);
	m_textures[name] = temp;
}

const sf::Font& ResourceManager::getFont()
{
	return m_font;
}
