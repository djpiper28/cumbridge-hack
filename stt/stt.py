import sys
import subprocess
import pyaudio
import wave
import os
import threading
import serial


def get_some_text(file_name: str) -> str:
    print(f"Transcribing {file_name} mate")
    output: str = "output"
    subprocess.run(f"vosk-transcriber --input {file_name} > {output}", shell=True)
    with open(output, "r") as f:
        data = f.read()
        print(f"WHHHHEEEEEEEYYYYYYYYYYYYYYYYYYYYYY WE HAVE SOME TEXT ME GEEZ: {data}")
        return data
    print("Dear sir/madam it appears that shit is fucked - please fix")
    return None


CRAPPY_FILE: str = "crappy_file"


def __reset_crappy_file() -> None:
    try:
        os.remove(CRAPPY_FILE)
    except:
        print("Seems legit mate")
    subprocess.Popen(f"./stop_button {CRAPPY_FILE}", shell=True)


button_down: bool = False

def wait_button_down(serial) -> None:
    global button_down
    button_down = False
    while "released" not in str(serial.readline()):
        pass
    button_down = True
    

def __record_audio() -> bool:
    global button_down
    return button_down


def get_some_audio(file_name: str, serial) -> None:
    threading.Thread(target=wait_button_down(serial), args=(serial,)).start()
    #__reset_crappy_file()
    chunk = 1024  # Record in chunks of 1024 samples
    sample_format = pyaudio.paInt16  # 16 bits per sample
    channels = 2
    fs = 44100  # Record at 44100 samples per second
    seconds = 3

    p = pyaudio.PyAudio()  # Create an interface to PortAudio

    print(f"Recording to {file_name}")

    stream = p.open(
        format=sample_format,
        channels=channels,
        rate=fs,
        frames_per_buffer=chunk,
        input=True,
    )

    frames = []  # Initialize array to store frames

    while __record_audio():
        for i in range(0, int(chunk)):
            data = stream.read(chunk)
            frames.append(data)

    # Stop and close the stream
    stream.stop_stream()
    stream.close()
    # Terminate the PortAudio interface
    p.terminate()

    print("Saving mate")

    # Save the recorded data as a WAV file
    wf = wave.open(file_name, "wb")
    wf.setnchannels(channels)
    wf.setsampwidth(p.get_sample_size(sample_format))
    wf.setframerate(fs)
    wf.writeframes(b"".join(frames))
    wf.close()


def convert_file(wav_f, mp3_f) -> None:
    print("Naughty transcode")
    try:
        os.remove(mp3_f)
    except:
        print("Eh seems fine mate")
    subprocess.run(
        f"ffmpeg -i {wav_f} -vn -ar 44100 -ac 2 -b:a 192k {mp3_f}", shell=True
    )


def do_stt(ser) -> str:
    FILE: str = "audio.wav"
    FILE_MP: str = FILE.replace("wav", "mp3")
    get_some_audio(FILE, ser)
    convert_file(FILE, FILE_MP)
    return get_some_text(FILE_MP)


if __name__ == "__main__":
    do_stt()
