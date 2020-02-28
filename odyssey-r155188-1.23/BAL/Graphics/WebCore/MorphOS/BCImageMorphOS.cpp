/*
 * Copyright (C) 2006 Apple Computer, Inc.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "owb-config.h"
#include "BitmapImage.h"
#include "SharedBuffer.h"
#include "WTFString.h"
#include "CString.h"
#include <clib/debug_protos.h>

namespace WebCore {

void BitmapImage::invalidatePlatformData()
{
}

static PassRefPtr<SharedBuffer> loadResourceSharedBufferFallback()
{
    return SharedBuffer::create(); // TODO: fallback image?
}

static PassRefPtr<SharedBuffer> loadResourceSharedBuffer(const char* name)
{
    String fullPath = "";
    String fname = String(name);

    if(fname.find(':') == notFound || !fname.endsWith(".info"))
    {
	fullPath = RESOURCE_PATH;
	fullPath.append(name);
	fullPath.append(".png");
    }
    else
    {
	fullPath = String(name);
    }

    RefPtr<SharedBuffer> buffer = SharedBuffer::createWithContentsOfFile(fullPath);
    if (buffer)
	return buffer.release();
    return loadResourceSharedBufferFallback();
}

PassRefPtr<Image> Image::loadPlatformResource(const char* name)
{
    RefPtr<BitmapImage> img = BitmapImage::create();
    RefPtr<SharedBuffer> buffer = loadResourceSharedBuffer(name);
    img->setData(buffer.release(), true);
    return img.release();
}

}    

