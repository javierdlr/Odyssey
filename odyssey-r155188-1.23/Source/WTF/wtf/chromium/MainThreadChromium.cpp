/*
* Copyright (C) 2009 Google Inc. All rights reserved.
* 
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are
* met:
* 
*     * Redistributions of source code must retain the above copyright
* notice, this list of conditions and the following disclaimer.
*     * Redistributions in binary form must reproduce the above
* copyright notice, this list of conditions and the following disclaimer
* in the documentation and/or other materials provided with the
* distribution.
*     * Neither the name of Google Inc. nor the names of its
* contributors may be used to endorse or promote products derived from
* this software without specific prior written permission.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
* A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
* OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
* SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
* LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
* THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "config.h"
#include "MainThread.h"

#include "Assertions.h"
#include "ChromiumThreading.h"
#include "Threading.h"
#include <wtf/Functional.h>

namespace WTF {

static ThreadIdentifier mainThreadIdentifier;

void initializeMainThread()
{
    static bool initializedMainThread;
    if (initializedMainThread)
        return;
    initializedMainThread = true;

    mainThreadIdentifier = currentThread();
}

void callOnMainThread(MainThreadFunction* function, void* context)
{
    ChromiumThreading::callOnMainThread(function, context);
}

static void callFunctionObject(void* context)
{
    Function<void()>* function = static_cast<Function<void()>*>(context);
    (*function)();
    delete function;
}

void callOnMainThread(const Function<void()>& function)
{
    callOnMainThread(callFunctionObject, new Function<void()>(function));
}

void callOnMainThreadAndWait(MainThreadFunction*, void*)
{
    ASSERT_NOT_REACHED();
}

void setMainThreadCallbacksPaused(bool)
{
    ASSERT_NOT_REACHED();
}

bool isMainThread()
{
    return currentThread() == mainThreadIdentifier;
}

} // namespace WTF

