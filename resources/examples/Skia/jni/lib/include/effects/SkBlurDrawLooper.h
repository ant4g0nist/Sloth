/*
 * Copyright 2008 The Android Open Source Project
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#ifndef SkBlurDrawLooper_DEFINED
#define SkBlurDrawLooper_DEFINED

#include "../core/SkDrawLooper.h"

/**
 *  DEPRECATED: No longer supported in Skia.
 */
namespace SkBlurDrawLooper {
    sk_sp<SkDrawLooper> SK_API Make(SkColor4f color, SkColorSpace* cs,
            SkScalar sigma, SkScalar dx, SkScalar dy);
    sk_sp<SkDrawLooper> SK_API Make(SkColor color, SkScalar sigma, SkScalar dx, SkScalar dy);
}  // namespace SkBlurDrawLooper

#endif
