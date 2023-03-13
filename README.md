# Hack Cambridge Spyder 2023
For this micro-hackathon, we made an emotional support horse named Andrew. You could speak to it, and it would speak back in a synthesised voice of our choosing (Piers Morgan was the most popular one we used). It was based off of the GPT-3.5 Turbo API with Eleven Labs’ voice synthesis. We had an E-Paper display show what was being said, and a button you could click to trigger the microphone to listen to your problems.

[Here's a video of it in action](https://youtu.be/YO5R1egwSto)

[Here's the presentation we made for him](https://docs.google.com/presentation/d/1gJqjIcAYpn-tLTlfQqI9fpoD1DlS-UnHounE9-nIMMw)

## Installation
Whisper requires FFMPEG
```
# on Ubuntu or Debian
sudo apt update && sudo apt install ffmpeg

# on Arch Linux
sudo pacman -S ffmpeg

# on MacOS using Homebrew (https://brew.sh/)
brew install ffmpeg

# on Windows using Chocolatey (https://chocolatey.org/)
choco install ffmpeg

# on Windows using Scoop (https://scoop.sh/)
scoop install ffmpeg
```


## Usage

Setup with the ENV variables
```
OPENAI_API_KEY=
ELEVENLABS_API_KEY=
VOICE_NAME=
```
