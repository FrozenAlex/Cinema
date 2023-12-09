#include "main.hpp"

#include "Screen/CustomVideoPlayer.hpp"

#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/PrimitiveType.hpp"
#include "UnityEngine/Video/VideoAspectRatio.hpp"
#include "UnityEngine/Video/VideoRenderMode.hpp"
#include "UnityEngine/Video/VideoAudioOutputMode.hpp"
#include "UnityEngine/Video/VideoSource.hpp"

using namespace UnityEngine;

DEFINE_TYPE(Cinema, CustomVideoPlayer);

#define RESOLVE_ICALL(name, ret, ...) reinterpret_cast<function_ptr_t<ret, UnityEngine::Video::VideoPlayer*, ## __VA_ARGS__>>(il2cpp_functions::resolve_icall("UnityEngine.Video.VideoPlayer::" #name));

namespace Cinema {

    void CustomVideoPlayer::Awake()
    {
        DEBUG("Creating CustomVideoPlayer");
//        CreateScreen();

        player = CreateVideoPlayer(get_transform());
        auto set_source = RESOLVE_ICALL(set_source, void, Video::VideoSource);
        set_source(player, Video::VideoSource::Url);
        auto set_renderMode = RESOLVE_ICALL(set_renderMode, void, Video::VideoRenderMode);
//        set_renderMode(player, Video::VideoRenderMode::);
//        auto set_targetTexture = RESOLVE_ICALL(set_targetTexture, void, RenderTexture*);
//        set_targetTexture(player, )

        auto set_playOnAwake = RESOLVE_ICALL(set_playOnAwake, void, bool);
        set_playOnAwake(player, false);
        auto set_waitForFirstFrame = RESOLVE_ICALL(set_waitForFirstFrame, void, bool);
        set_waitForFirstFrame(player, true);

        DEBUG("Adding event callbacks");
        videoPlayerErrorReceived = {&CustomVideoPlayer::VideoPlayerErrorReceived, this};
        player->errorReceived += videoPlayerErrorReceived;
        videoPlayerPrepareComplete = {&CustomVideoPlayer::VideoPlayerPrepareComplete, this};
        player->prepareCompleted += videoPlayerPrepareComplete;
        videoPlayerStarted = {&CustomVideoPlayer::VideoPlayerStarted, this};
        player->started += videoPlayerStarted;
        videoPlayerFinished = {&CustomVideoPlayer::VideoPlayerFinished, this};
        player->loopPointReached += videoPlayerFinished;

        DEBUG("Creating audio source");
        videoPlayerAudioSource = get_gameObject()->AddComponent<AudioSource*>();
        auto set_audioOutputMode = RESOLVE_ICALL(set_audioOutputMode, void, Video::VideoAudioOutputMode);
        set_audioOutputMode(player, Video::VideoAudioOutputMode::AudioSource);
        auto SetTargetAudioSource = RESOLVE_ICALL(SetTargetAudioSource, void, uint16_t, AudioSource*);
        SetTargetAudioSource(player, 0, videoPlayerAudioSource);
    }


    Video::VideoPlayer* CustomVideoPlayer::CreateVideoPlayer(UnityEngine::Transform* parent)
    {
         INFO("Creating VideoPlayer");
         GameObject* screenGo = GameObject::CreatePrimitive(PrimitiveType::Plane);
         screenGo->get_transform()->set_parent(parent);
         GameObject::DontDestroyOnLoad(screenGo);

         auto material = Resources::FindObjectsOfTypeAll<Material*>().LastOrDefault([](Material* x) {
             return x->get_name() == "PyroVideo (Instance)";
         });
        
         if(material)
             screenGo->GetComponent<Renderer*>()->set_material(material);
         else
             screenGo->GetComponent<Renderer*>()->set_material(Material::New_ctor(Shader::Find("Unlit/Texture")));
         screenGo->get_transform()->set_position(Vector3{0.0f, 12.4f, 67.8f});
         screenGo->get_transform()->set_rotation(Quaternion::Euler(90.0f, 270.0f, 90.0f));
         screenGo->get_transform()->set_localScale(Vector3(5.11, 1, 3));

         auto videoPlayer = screenGo->AddComponent<Video::VideoPlayer*>();

         auto cinemaScreen = screenGo->GetComponent<Renderer*>();
         if(cinemaScreen)
         {
             static auto set_targetMaterialRenderer = RESOLVE_ICALL(set_targetMaterialRenderer, void, Renderer*);
             set_targetMaterialRenderer(videoPlayer, cinemaScreen);
         }

         return videoPlayer;
    }

    void CustomVideoPlayer::OnDestroy()
    {}

    void CustomVideoPlayer::CreateScreen()
    {}

    void CustomVideoPlayer::Play()
    {
        player->Play();
    }

    void CustomVideoPlayer::Pause()
    {
        static auto func = RESOLVE_ICALL(Pause, void);
        func(player);
    }

    void CustomVideoPlayer::Prepare()
    {
        static auto func = RESOLVE_ICALL(Prepare, void);
        func(player);
    }

    void CustomVideoPlayer::VideoPlayerErrorReceived(UnityEngine::Video::VideoPlayer *source, StringW message)
    {}

    void CustomVideoPlayer::VideoPlayerPrepareComplete(UnityEngine::Video::VideoPlayer *source)
    {}

    void CustomVideoPlayer::VideoPlayerFinished(UnityEngine::Video::VideoPlayer *source)
    {}

    void CustomVideoPlayer::VideoPlayerStarted(UnityEngine::Video::VideoPlayer *source)
    {}

    float CustomVideoPlayer::get_playbackSpeed()
    {
        static auto func = RESOLVE_ICALL(get_playbackSpeed, float);
        return func(player);
    }

    void CustomVideoPlayer::set_playbackSpeed(float value)
    {
        player->set_playbackSpeed(value);
    }

    StringW CustomVideoPlayer::get_url()
    {
        static auto func = RESOLVE_ICALL(get_url, StringW);
        return func(player);
    }

    void CustomVideoPlayer::set_url(StringW value)
    {
        static auto func = RESOLVE_ICALL(set_url, void, StringW);
        func(player, value);
    }

    void CustomVideoPlayer::set_volume(float value)
    {
        static auto func = RESOLVE_ICALL(set_volume, void, float);
        func(player, value);
    }

    bool CustomVideoPlayer::get_isPlaying()
    {
        return player->get_isPlaying();
    }

    bool CustomVideoPlayer::get_isPrepared()
    {
        static auto func = RESOLVE_ICALL(get_isPrepared, bool);
        return func(player);
    }

    void CustomVideoPlayer::set_time(double value)
    {
        static auto func = RESOLVE_ICALL(set_time, void, double);
        func(player, value);
    }

    void CustomVideoPlayer::set_sendFrameReadyEvents(bool value)
    {
        static auto func = RESOLVE_ICALL(set_sendFrameReadyEvents, void, bool);
        func(player, value);
    }
}