import os

# 1. Получаем список файлов и сортируем их строго по номеру
path = 'clean_frames'
files = sorted([f for f in os.listdir(path) if f.endswith('.data')], 
               key=lambda x: int(''.join(filter(str.isdigit, x))))

if not files:
    print("Ошибка: папка clean_frames пуста!")
else:
    print(f"Склеиваю {len(files)} файлов в один поток...")
    
    # Склеиваем всё в один файл all_frames.raw
    with open('all_frames.raw', 'wb') as outfile:
        for fname in files:
            with open(os.path.join(path, fname), 'rb') as infile:
                outfile.write(infile.read())
    
    print("Склейка завершена. Запускаю конвертацию...")

    # 2. Конвертируем один большой файл в MP4
    # Мы убираем -i frame_%03d и просто даем один входной файл
    !ffmpeg -y -f rawvideo -pixel_format rgba -video_size 1024x768 -r 24 \
            -i all_frames.raw -c:v libx264 -pix_fmt yuv420p result_video.mp4

    if os.path.exists('result_video.mp4'):
        print("\n--- ПОБЕДА! Видео создано: result_video.mp4 ---")
        # Удаляем временный гигантский файл, чтобы не занимать место
        os.remove('all_frames.raw')
    else:
        print("\n--- Что-то пошло не так. Проверьте вывод FFmpeg выше. ---")

#higher quality 
#"""
#!ffmpeg -y -f rawvideo -pixel_format rgba -video_size 1024x768 -r 60 \
#        -i all_frames.raw \
#        -c:v libx264 -crf 17 -preset slow -pix_fmt yuv420p high_quality_video.mp4
#
#print("Видео высокого качества готово: high_quality_video.mp4")
#
#"""