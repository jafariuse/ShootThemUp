#pragma once

class AnimUtils
{
public:
    template <typename T> static  T* FindNotifyByClass(UAnimSequenceBase* Animation)
    {
        if (!Animation) return nullptr;
        const  TArray<FAnimNotifyEvent> NotifyEvents = Animation->Notifies;
        for (auto Event:NotifyEvents)
        {
            auto  AnimNotify = Cast<T>(Event.Notify);
            if (AnimNotify) return AnimNotify;
        }
        return nullptr;
    }
    
};
