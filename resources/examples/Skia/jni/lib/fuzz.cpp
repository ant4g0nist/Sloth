#define SK_BUILD_FOR_ANDROID

#include <stdio.h>
#include <stdint.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "fuzz.h"
// #include "include/codec/SkAndroidCodec.h"
// #include "include/core/SkBitmap.h"
// #include "include/codec/SkCodec.h"
// #include "include/core/SkString.h"
// #include "include/core/SkPngChunkReader.h"

extern "C" int libQemuFuzzerTestOneInput(const uint8_t *Data, size_t Size)
{
	if (Size <5 && Size > 4096)
		return 0;

	if(Data[0] == 0xde)
	{
		if(Data[1] == 0xad)
		{
			if(Data[2] == 0xbe)
			{
				if(Data[4] == 0xef)
				{
					if(Data[55] == 0xca)
					{
						char * ptr = (char*) 0x61616161;
						ptr[0]=0;
					}
					
				}
				
			}
			
		}

	}

	return 0;
}

// extern "C" int libQemuFuzzerTestOneInput(const uint8_t *Data, size_t Size)
// {
// 	if (Size <1 && Size > 4096)
// 		return 0;

// 	void * DataMa = malloc(Size);
// 	memcpy(DataMa, Data, Size);

// 	sk_sp<SkData> data = SkData::MakeFromMalloc(DataMa, Size);
// 	SkCodec::Result result;

// 	std::unique_ptr<SkAndroidCodec> codec = SkAndroidCodec::MakeFromData(std::move(data), nullptr);

// 	if (!codec) {
// 		return 0;
// 	}

// 	SkImageInfo info = codec->getInfo();
// 	const int width  = info.width();
// 	const int height = info.height();

// 	SkColorType decodeColorType = kN32_SkColorType;
// 	SkBitmap::HeapAllocator defaultAllocator;
// 	SkBitmap::Allocator* decodeAllocator = &defaultAllocator;
// 	SkAlphaType alphaType = codec->computeOutputAlphaType(/*requireUnpremultiplied=*/false);
// 	const SkImageInfo decodeInfo = SkImageInfo::Make(width, height, decodeColorType, alphaType);

// 	SkImageInfo bitmapInfo = decodeInfo;
// 	SkBitmap decodingBitmap;
// 	if (!decodingBitmap.setInfo(bitmapInfo) ||
// 		!decodingBitmap.tryAllocPixels(decodeAllocator)) {
// 		return 1;
// 	}

// 	result = codec->getAndroidPixels(decodeInfo, decodingBitmap.getPixels(), decodingBitmap.rowBytes());

// 	return 0;
// }
