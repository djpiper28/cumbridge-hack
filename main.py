import openai
import os
import stt.stt
from elevenlabslib import *
from dotenv import load_dotenv

load_dotenv()

user = ElevenLabsUser(os.getenv("ELEVENLABS_API_KEY"))
voice = user.get_voices_by_name(os.getenv("VOICE_NAME"))[0]

openai.api_key = os.getenv("OPENAI_API_KEY")

messages = [
    {
        "role": "system",
        "content": "You are simulating a conversation between a person and an emotional support horse named andrew who also does therapy. You play the role of the horse.",
    }
]


while True:
    # Get the user's input
    input("Press enter to speak to the geezer")
    user_input = stt.stt.do_stt()

    # Add the user's input to the messages
    messages.append({"role": "user", "content": user_input})

    print("Asking the horse")
    response = openai.ChatCompletion.create(
        model="gpt-3.5-turbo",
        messages=messages,
        temperature=0.9,
        max_tokens=150,
    )

    msgResponse = response.choices[0].message.content

    # Add the bot's response to the messages
    messages.append({"role": "system", "content": msgResponse})

    print(f"Getting audio for {msgResponse}")
    voice.generate_and_play_audio(msgResponse, playInBackground=False)
