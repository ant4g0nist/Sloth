/*
 * Copyright 2016 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkOverdrawCanvas_DEFINED
#define SkOverdrawCanvas_DEFINED

#include "../core/SkCanvasVirtualEnforcer.h"
#include "../utils/SkNWayCanvas.h"

/**
 *  Captures all drawing commands.  Rather than draw the actual content, this device
 *  increments the alpha channel of each pixel every time it would have been touched
 *  by a draw call.  This is useful for detecting overdraw.
 */
class SK_API SkOverdrawCanvas : public SkCanvasVirtualEnforcer<SkNWayCanvas> {
public:
    /* Does not take ownership of canvas */
    SkOverdrawCanvas(SkCanvas*);

    void onDrawTextBlob(const SkTextBlob*, SkScalar, SkScalar, const SkPaint&) override;
    void onDrawPatch(const SkPoint[12], const SkColor[4], const SkPoint[4], SkBlendMode,
                     const SkPaint&) override;
    void onDrawPaint(const SkPaint&) override;
    void onDrawBehind(const SkPaint& paint) override;
    void onDrawRect(const SkRect&, const SkPaint&) override;
    void onDrawRegion(const SkRegion&, const SkPaint&) override;
    void onDrawOval(const SkRect&, const SkPaint&) override;
    void onDrawArc(const SkRect&, SkScalar, SkScalar, bool, const SkPaint&) override;
    void onDrawDRRect(const SkRRect&, const SkRRect&, const SkPaint&) override;
    void onDrawRRect(const SkRRect&, const SkPaint&) override;
    void onDrawPoints(PointMode, size_t, const SkPoint[], const SkPaint&) override;
    void onDrawVerticesObject(const SkVertices*, SkBlendMode, const SkPaint&) override;
    void onDrawAtlas(const SkImage*, const SkRSXform[], const SkRect[], const SkColor[],
                     int, SkBlendMode, const SkRect*, const SkPaint*) override;
    void onDrawPath(const SkPath&, const SkPaint&) override;
    void onDrawImage(const SkImage*, SkScalar, SkScalar, const SkPaint*) override;
    void onDrawImageRect(const SkImage*, const SkRect*, const SkRect&, const SkPaint*,
                         SrcRectConstraint) override;
    void onDrawImageNine(const SkImage*, const SkIRect&, const SkRect&, const SkPaint*) override;
    void onDrawImageLattice(const SkImage*, const Lattice&, const SkRect&, const SkPaint*) override;
    void onDrawDrawable(SkDrawable*, const SkMatrix*) override;
    void onDrawPicture(const SkPicture*, const SkMatrix*, const SkPaint*) override;

    void onDrawAnnotation(const SkRect&, const char key[], SkData* value) override;
    void onDrawShadowRec(const SkPath&, const SkDrawShadowRec&) override;

    void onDrawEdgeAAQuad(const SkRect&, const SkPoint[4], SkCanvas::QuadAAFlags, const SkColor4f&,
                          SkBlendMode) override;
    void onDrawEdgeAAImageSet(const ImageSetEntry[], int count, const SkPoint[], const SkMatrix[],
                              const SkPaint*, SrcRectConstraint) override;

private:
    void drawPosTextCommon(const SkGlyphID[], int, const SkScalar[], int, const SkPoint&,
                           const SkFont&, const SkPaint&);

    inline SkPaint overdrawPaint(const SkPaint& paint);

    SkPaint   fPaint;

    using INHERITED = SkCanvasVirtualEnforcer<SkNWayCanvas>;
};

#endif
