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

#include "../Graphics/GraphicsDefs.h"
#include "../UI/UIElement.h"

namespace Urho3D
{

class Texture;
class Texture2D;

/// %Image %UI element with optional border.
class URHO3D_API BorderImage : public UIElement
{
    URHO3D_OBJECT(BorderImage, UIElement);

public:
    /// Construct.
    explicit BorderImage(Context* context);
    /// Destruct.
    ~BorderImage() override;
    /// Register object factory.
    /// @nobind
    static void RegisterObject(Context* context);

    /// Return UI rendering batches.
    void GetBatches(PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor) override;

    /// Set texture.
    /// @property
    void SetTexture(Texture* texture);
    /// Set part of texture to use as the image.
    /// @property
    void SetImageRect(const IntRect& rect);
    /// Use whole texture as the image.
    void SetFullImageRect();
    /// Set border dimensions on the screen.
    /// @property
    void SetBorder(const IntRect& rect);
    /// Set border dimensions on the image. If zero (default) uses the screen dimensions, resulting in pixel-perfect borders.
    /// @property
    void SetImageBorder(const IntRect& rect);
    /// Set offset to image rectangle used on hover.
    /// @property
    void SetHoverOffset(const IntVector2& offset);
    /// Set offset to image rectangle used on hover.
    void SetHoverOffset(int x, int y);
    /// Set offset to image rectangle used when disabled.
    /// @property
    void SetDisabledOffset(const IntVector2& offset);
    /// Set offset to image rectangle used when disabled.
    void SetDisabledOffset(int x, int y);
    /// Set blend mode.
    /// @property
    void SetBlendMode(BlendMode mode);
    /// Set tiled mode.
    /// @property
    void SetTiled(bool enable);
    /// Set material for custom rendering.
    /// @property
    void SetMaterial(Material* material);

    /// Return texture.
    /// @property
    Texture* GetTexture() const { return texture_; }

    /// Return image rectangle.
    /// @property
    const IntRect& GetImageRect() const { return imageRect_; }

    /// Return border screen dimensions.
    /// @property
    const IntRect& GetBorder() const { return border_; }

    /// Return border image dimensions. Zero rect uses border screen dimensions.
    /// @property
    const IntRect& GetImageBorder() const { return imageBorder_; }

    /// Return offset to image rectangle used on hover.
    /// @property
    const IntVector2& GetHoverOffset() const { return hoverOffset_; }

    /// Return offset to image rectangle used when disabled.
    /// @property
    const IntVector2& GetDisabledOffset() const { return disabledOffset_; }

    /// Return blend mode.
    /// @property
    BlendMode GetBlendMode() const { return blendMode_; }

    /// Return whether is tiled.
    /// @property
    bool IsTiled() const { return tiled_; }

    /// Get material used for custom rendering.
    /// @property
    Material* GetMaterial() const;

    /// Set texture attribute.
    void SetTextureAttr(const ResourceRef& value);
    /// Return texture attribute.
    ResourceRef GetTextureAttr() const;

    /// Set material attribute.
    void SetMaterialAttr(const ResourceRef& value);
    /// Get material attribute.
    ResourceRef GetMaterialAttr() const;
protected:
    /// Return UI rendering batches with offset to image rectangle.
    void GetBatches
        (PODVector<UIBatch>& batches, PODVector<float>& vertexData, const IntRect& currentScissor, const IntVector2& offset);

    /// Texture.
    SharedPtr<Texture> texture_;
    /// Image rectangle.
    IntRect imageRect_;
    /// Border dimensions on screen.
    IntRect border_;
    /// Border dimensions on the image.
    IntRect imageBorder_;
    /// Offset to image rectangle on hover.
    IntVector2 hoverOffset_;
    /// Offset to image rectangle when disabled.
    IntVector2 disabledOffset_;
    /// Blend mode flag.
    BlendMode blendMode_;
    /// Tiled flag.
    bool tiled_;
    /// Material used for custom rendering.
    SharedPtr<Material> material_;
};

}
