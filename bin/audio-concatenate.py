import os
import numpy as np
import wave

def concatenate_wav_files(input_dir, output_file, target_duration_seconds, sample_rate=48000, sample_width=2):
    """
    Concatenates multiple .wav files into a single PCM file with a specified duration.
    
    Parameters:
        input_dir (str): Directory containing the input .wav files.
        output_file (str): Path to save the concatenated output file.
        target_duration_seconds (int): Desired duration of the output file in seconds.
        sample_rate (int): Sampling rate of the audio files (default is 48000 Hz).
        sample_width (int): Sample width in bytes (default is 2 for PCM16).
    """
    # Initialize an empty list to store audio data
    audio_data = []

    # Iterate through all .wav files in the input directory
    for filename in sorted(os.listdir(input_dir)):
        if filename.endswith(".wav"):
            file_path = os.path.join(input_dir, filename)
            
            # Open the .wav file
            with wave.open(file_path, 'rb') as wav_file:
                # Ensure the file matches the expected format
                if wav_file.getnchannels() != 1 or wav_file.getsampwidth() != sample_width or wav_file.getframerate() != sample_rate:
                    raise ValueError(f"File {filename} does not match the expected format (Mono, PCM16, 48kHz).")
                
                # Read the audio frames and append to the list
                frames = wav_file.readframes(wav_file.getnframes())
                audio_data.append(np.frombuffer(frames, dtype=np.int16))

    # Concatenate all audio data into a single array
    concatenated_audio = np.concatenate(audio_data)

    # Calculate the number of samples needed for the target duration
    target_samples = target_duration_seconds * sample_rate

    # Truncate or pad the concatenated audio to match the target duration
    if len(concatenated_audio) > target_samples:
        concatenated_audio = concatenated_audio[:target_samples]  # Truncate if too long
    elif len(concatenated_audio) < target_samples:
        padding = np.zeros(target_samples - len(concatenated_audio), dtype=np.int16)
        concatenated_audio = np.concatenate([concatenated_audio, padding])  # Pad with silence if too short

    # Write the concatenated audio to the output file
    with wave.open(output_file, 'wb') as output_wav:
        output_wav.setnchannels(1)  # Mono
        output_wav.setsampwidth(sample_width)
        output_wav.setframerate(sample_rate)
        output_wav.writeframes(concatenated_audio.tobytes())

# Example usage
input_directory = "/Users/royzheng/repo/rnnoise/data/en_ng_female"  # Replace with your directory path
output_file = "/Users/royzheng/repo/rnnoise/data/en_ng_female/clean_audio.wav"  # Replace with your desired output path
target_duration = 400  # 6 minutes and 40 seconds in seconds

concatenate_wav_files(input_directory, output_file, target_duration)
