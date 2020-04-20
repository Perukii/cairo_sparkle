
struct casp_audio{

    Mix_Music *music;
    void setup_audio(){
        Mix_Init(MIX_INIT_MP3);
    }

    void play_music(const char * _file, uint _loop){
        Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
        music = Mix_LoadMUS(_file);
        Mix_PlayMusic(music, _loop);
    }

    void pause_music(){
        Mix_PauseMusic();
    } 

    ~casp_audio(){
        Mix_FreeMusic(music);
    }

};