//
// Copyright (c) 2008-2025 the U3D project.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include "../Precompiled.h"

#include "../Core/Context.h"
#include "../IO/AbstractFile.h"
#include "../IO/FileSystem.h"
#include "../IO/Log.h"
#include "../Resource/XMLFile.h"
#include "../Resource/JSONFile.h"
#include "../Scene/ObjectAnimation.h"
#include "../Scene/SceneEvents.h"
#include "../Scene/ValueAnimation.h"
#include "../Scene/ValueAnimationInfo.h"

#include "../DebugNew.h"

namespace Urho3D
{

const char* wrapModeNames[] =
{
    "Loop",
    "Once",
    "Clamp",
    nullptr
};

ObjectAnimation::ObjectAnimation(Context* context) :
    Resource(context)
{
}

ObjectAnimation::~ObjectAnimation() = default;

void ObjectAnimation::RegisterObject(Context* context)
{
    context->RegisterFactory<ObjectAnimation>();
}

bool ObjectAnimation::BeginLoad(Deserializer& source)
{
    String extension = GetExtension(source.GetName());

    if (extension == ".xml")
    {
        XMLFile xmlFile(context_);
        if (xmlFile.Load(source))
            return LoadXML(xmlFile.GetRoot());
    }
    else if (extension == ".json")
    {
        JSONFile jsonFile(context_);
        if (jsonFile.Load(source))
            return LoadJSON(jsonFile.GetRoot());
    }

    return false;
}

bool ObjectAnimation::Save(Serializer& dest) const
{
    return Save(dest, ".xml");
}

bool ObjectAnimation::Save(Serializer& dest, const String& extension) const
{
    if (extension == ".xml")
    {
        XMLFile xmlFile(context_);
        XMLElement rootElem = xmlFile.CreateRoot("objectanimation");
        if (!SaveXML(rootElem))
        {
            URHO3D_LOGERROR("ObjectAnimation SaveXML Error");
            return false;
        }

        return xmlFile.Save(dest);
    }
    else if (extension == ".json")
    {
        JSONFile jsonFile(context_);
        jsonFile.GetRoot() = "objectanimation";
        if (!SaveJSON(jsonFile.GetRoot()))
        {
            URHO3D_LOGERROR("ObjectAnimation SaveJSON Error");
            return false;
        }

        return jsonFile.Save(dest);
    }

    return false;
}

bool ObjectAnimation::LoadXML(const XMLElement& source)
{
    attributeAnimationInfos_.Clear();

    XMLElement animElem;
    animElem = source.GetChild("attributeanimation");
    while (animElem)
    {
        String name = animElem.GetAttribute("name");

        SharedPtr<ValueAnimation> animation(new ValueAnimation(context_));
        if (!animation->LoadXML(animElem))
            return false;

        String wrapModeString = animElem.GetAttribute("wrapmode");
        WrapMode wrapMode = WM_LOOP;
        for (int i = 0; i <= WM_CLAMP; ++i)
        {
            if (wrapModeString == wrapModeNames[i])
            {
                wrapMode = (WrapMode)i;
                break;
            }
        }

        float speed = animElem.GetFloat("speed");
        AddAttributeAnimation(name, animation, wrapMode, speed);

        animElem = animElem.GetNext("attributeanimation");
    }

    return true;
}

bool ObjectAnimation::SaveXML(XMLElement& dest) const
{
    for (HashMap<String, SharedPtr<ValueAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
    {
        XMLElement animElem = dest.CreateChild("attributeanimation");
        animElem.SetAttribute("name", i->first_);

        const ValueAnimationInfo* info = i->second_;
        if (!info->GetAnimation()->SaveXML(animElem))
            return false;

        animElem.SetAttribute("wrapmode", wrapModeNames[info->GetWrapMode()]);
        animElem.SetFloat("speed", info->GetSpeed());
    }

    return true;
}

bool ObjectAnimation::LoadJSON(const JSONValue& source)
{
    attributeAnimationInfos_.Clear();

    JSONValue attributeAnimationsValue = source.Get("attributeanimations");
    if (attributeAnimationsValue.IsNull())
        return true;
    if (!attributeAnimationsValue.IsObject())
        return true;

    const JSONObject& attributeAnimationsObject = attributeAnimationsValue.GetObject();

    for (JSONObject::ConstIterator it = attributeAnimationsObject.Begin(); it != attributeAnimationsObject.End(); it++)
    {
        String name = it->first_;
        JSONValue value = it->second_;
        SharedPtr<ValueAnimation> animation(new ValueAnimation(context_));
        if (!animation->LoadJSON(value))
            return false;

        String wrapModeString = value.Get("wrapmode").GetString();
        WrapMode wrapMode = WM_LOOP;
        for (int i = 0; i <= WM_CLAMP; ++i)
        {
            if (wrapModeString == wrapModeNames[i])
            {
                wrapMode = (WrapMode)i;
                break;
            }
        }

        float speed = value.Get("speed").GetFloat();
        AddAttributeAnimation(name, animation, wrapMode, speed);
    }

    return true;
}

bool ObjectAnimation::SaveJSON(JSONValue& dest) const
{
    JSONValue attributeAnimationsValue;

    for (HashMap<String, SharedPtr<ValueAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
    {
        JSONValue animValue;
        animValue.Set("name", i->first_);

        const ValueAnimationInfo* info = i->second_;
        if (!info->GetAnimation()->SaveJSON(animValue))
            return false;

        animValue.Set("wrapmode", wrapModeNames[info->GetWrapMode()]);
        animValue.Set("speed", (float) info->GetSpeed());

        attributeAnimationsValue.Set(i->first_, animValue);
    }

    dest.Set("attributeanimations", attributeAnimationsValue);
    return true;
}

void ObjectAnimation::AddAttributeAnimation(const String& name, ValueAnimation* attributeAnimation, WrapMode wrapMode, float speed)
{
    if (!attributeAnimation)
        return;

    attributeAnimation->SetOwner(this);
    attributeAnimationInfos_[name] = new ValueAnimationInfo(attributeAnimation, wrapMode, speed);

    SendAttributeAnimationAddedEvent(name);
}

void ObjectAnimation::RemoveAttributeAnimation(const String& name)
{
    HashMap<String, SharedPtr<ValueAnimationInfo> >::Iterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
    {
        SendAttributeAnimationRemovedEvent(name);

        i->second_->GetAnimation()->SetOwner(nullptr);
        attributeAnimationInfos_.Erase(i);
    }
}

void ObjectAnimation::RemoveAttributeAnimation(ValueAnimation* attributeAnimation)
{
    if (!attributeAnimation)
        return;

    for (HashMap<String, SharedPtr<ValueAnimationInfo> >::Iterator i = attributeAnimationInfos_.Begin();
         i != attributeAnimationInfos_.End(); ++i)
    {
        if (i->second_->GetAnimation() == attributeAnimation)
        {
            SendAttributeAnimationRemovedEvent(i->first_);

            attributeAnimation->SetOwner(nullptr);
            attributeAnimationInfos_.Erase(i);
            return;
        }
    }
}

ValueAnimation* ObjectAnimation::GetAttributeAnimation(const String& name) const
{
    ValueAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetAnimation() : nullptr;
}

WrapMode ObjectAnimation::GetAttributeAnimationWrapMode(const String& name) const
{
    ValueAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetWrapMode() : WM_LOOP;
}

float ObjectAnimation::GetAttributeAnimationSpeed(const String& name) const
{
    ValueAnimationInfo* info = GetAttributeAnimationInfo(name);
    return info ? info->GetSpeed() : 1.0f;
}

ValueAnimationInfo* ObjectAnimation::GetAttributeAnimationInfo(const String& name) const
{
    HashMap<String, SharedPtr<ValueAnimationInfo> >::ConstIterator i = attributeAnimationInfos_.Find(name);
    if (i != attributeAnimationInfos_.End())
        return i->second_;
    return nullptr;
}

void ObjectAnimation::SendAttributeAnimationAddedEvent(const String& name)
{
    using namespace AttributeAnimationAdded;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_OBJECTANIMATION] = this;
    eventData[P_ATTRIBUTEANIMATIONNAME] = name;
    SendEvent(E_ATTRIBUTEANIMATIONADDED, eventData);
}

void ObjectAnimation::SendAttributeAnimationRemovedEvent(const String& name)
{
    using namespace AttributeAnimationRemoved;
    VariantMap& eventData = GetEventDataMap();
    eventData[P_OBJECTANIMATION] = this;
    eventData[P_ATTRIBUTEANIMATIONNAME] = name;
    SendEvent(E_ATTRIBUTEANIMATIONREMOVED, eventData);
}

}
