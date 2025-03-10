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

#pragma once

#include "../UI/BorderImage.h"

namespace Urho3D
{

/// %Slider bar %UI element.
class URHO3D_API Slider : public BorderImage
{
    URHO3D_OBJECT(Slider, BorderImage);

public:
    /// Construct.
    explicit Slider(Context* context);
    /// Destruct.
    ~Slider() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Perform UI element update.
    void Update(float timeStep) override;
    /// React to mouse hover.
    void OnHover(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse click begin.
    void OnClickBegin
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse click end.
    void OnClickEnd
        (const IntVector2& position, const IntVector2& screenPosition, MouseButton button, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor,
            UIElement* beginElement) override;
    /// React to mouse drag begin.
    void
        OnDragBegin(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags buttons, QualifierFlags qualifiers, Cursor* cursor) override;
    /// React to mouse drag motion.
    void OnDragMove
        (const IntVector2& position, const IntVector2& screenPosition, const IntVector2& deltaPos, MouseButtonFlags buttons, QualifierFlags qualifiers,
            Cursor* cursor) override;
    /// React to mouse drag end.
    void
        OnDragEnd(const IntVector2& position, const IntVector2& screenPosition, MouseButtonFlags dragButtons, MouseButtonFlags releaseButtons, Cursor* cursor) override;
    /// React to resize.
    void OnResize(const IntVector2& newSize, const IntVector2& delta) override;

    /// Set orientation type.
    /// @property
    void SetOrientation(Orientation orientation);
    /// Set slider range maximum value (minimum value is always 0).
    /// @property
    void SetRange(float range);
    /// Set slider current value.
    /// @property
    void SetValue(float value);
    /// Change value by a delta.
    void ChangeValue(float delta);
    /// Set paging minimum repeat rate (number of events per second).
    /// @property
    void SetRepeatRate(float rate);

    /// Return orientation type.
    /// @property
    Orientation GetOrientation() const { return orientation_; }

    /// Return slider range.
    /// @property
    float GetRange() const { return range_; }

    /// Return slider current value.
    /// @property
    float GetValue() const { return value_; }

    /// Return knob element.
    /// @property
    BorderImage* GetKnob() const { return knob_; }

    /// Return paging minimum repeat rate (number of events per second).
    /// @property
    float GetRepeatRate() const { return repeatRate_; }

protected:
    /// Filter implicit attributes in serialization process.
    bool FilterImplicitAttributes(XMLElement& dest) const override;
    /// Update slider knob position & size.
    void UpdateSlider();
    /// Send slider page event.
    void Page(const IntVector2& position, bool pressed);

    /// Slider knob.
    SharedPtr<BorderImage> knob_;
    /// Orientation.
    Orientation orientation_;
    /// Slider range.
    float range_;
    /// Slider current value.
    float value_;
    /// Internal flag of whether the slider is being dragged.
    bool dragSlider_;
    /// Original mouse cursor position at drag begin.
    IntVector2 dragBeginCursor_;
    /// Original slider position at drag begin.
    IntVector2 dragBeginPosition_;
    /// Paging repeat rate.
    float repeatRate_;
    /// Paging minimum repeat timer.
    Timer repeatTimer_;
};

}
