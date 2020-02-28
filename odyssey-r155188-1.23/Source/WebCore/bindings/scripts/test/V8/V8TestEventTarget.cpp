/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include "config.h"
#include "V8TestEventTarget.h"

#include "BindingState.h"
#include "ContextFeatures.h"
#include "ExceptionCode.h"
#include "Frame.h"
#include "RuntimeEnabledFeatures.h"
#include "V8Binding.h"
#include "V8Collection.h"
#include "V8DOMWrapper.h"
#include "V8Event.h"
#include "V8EventListenerList.h"
#include "V8Node.h"
#include <wtf/UnusedParam.h>

#if ENABLE(BINDING_INTEGRITY)
#if defined(OS_WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestEventTarget@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore15TestEventTargetE[]; }
#endif
#endif // ENABLE(BINDING_INTEGRITY)

namespace WebCore {

#if ENABLE(BINDING_INTEGRITY)
// This checks if a DOM object that is about to be wrapped is valid.
// Specifically, it checks that a vtable of the DOM object is equal to
// a vtable of an expected class.
// Due to a dangling pointer, the DOM object you are wrapping might be
// already freed or realloced. If freed, the check will fail because
// a free list pointer should be stored at the head of the DOM object.
// If realloced, the check will fail because the vtable of the DOM object
// differs from the expected vtable (unless the same class of DOM object
// is realloced on the slot).
inline void checkTypeOrDieTrying(TestEventTarget* object)
{
    void* actualVTablePointer = *(reinterpret_cast<void**>(object));
#if defined(OS_WIN)
    void* expectedVTablePointer = reinterpret_cast<void*>(__identifier("??_7TestEventTarget@WebCore@@6B@"));
#else
    void* expectedVTablePointer = &_ZTVN7WebCore15TestEventTargetE[2];
#endif
    if (actualVTablePointer != expectedVTablePointer)
        CRASH();
}
#endif // ENABLE(BINDING_INTEGRITY)

WrapperTypeInfo V8TestEventTarget::info = { V8TestEventTarget::GetTemplate, V8TestEventTarget::derefObject, 0, V8TestEventTarget::toEventTarget, 0, V8TestEventTarget::installPerContextPrototypeProperties, 0, WrapperTypeObjectPrototype };

namespace TestEventTargetV8Internal {

template <typename T> void V8_USE(T) { }

static v8::Handle<v8::Value> itemMethod(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    TestEventTarget* imp = V8TestEventTarget::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    V8TRYCATCH(int, index, toUInt32(args[0]));
    if (UNLIKELY(index < 0)) {
        ec = INDEX_SIZE_ERR;
        goto fail;
    }
    return toV8(imp->item(index), args.Holder(), args.GetIsolate());
    }
    fail:
    return setDOMException(ec, args.GetIsolate());
}

static v8::Handle<v8::Value> itemMethodCallback(const v8::Arguments& args)
{
    return TestEventTargetV8Internal::itemMethod(args);
}

static v8::Handle<v8::Value> addEventListenerMethod(const v8::Arguments& args)
{
    RefPtr<EventListener> listener = V8EventListenerList::getEventListener(args[1], false, ListenerFindOrCreate);
    if (listener) {
        V8TRYCATCH_FOR_V8STRINGRESOURCE(V8StringResource<WithNullCheck>, stringResource, args[0]);
        V8TestEventTarget::toNative(args.Holder())->addEventListener(stringResource, listener, args[2]->BooleanValue());
        createHiddenDependency(args.Holder(), args[1], V8TestEventTarget::eventListenerCacheIndex, args.GetIsolate());
    }
    return v8Undefined();
}

static v8::Handle<v8::Value> addEventListenerMethodCallback(const v8::Arguments& args)
{
    return TestEventTargetV8Internal::addEventListenerMethod(args);
}

static v8::Handle<v8::Value> removeEventListenerMethod(const v8::Arguments& args)
{
    RefPtr<EventListener> listener = V8EventListenerList::getEventListener(args[1], false, ListenerFindOnly);
    if (listener) {
        V8TRYCATCH_FOR_V8STRINGRESOURCE(V8StringResource<WithNullCheck>, stringResource, args[0]);
        V8TestEventTarget::toNative(args.Holder())->removeEventListener(stringResource, listener.get(), args[2]->BooleanValue());
        removeHiddenDependency(args.Holder(), args[1], V8TestEventTarget::eventListenerCacheIndex, args.GetIsolate());
    }
    return v8Undefined();
}

static v8::Handle<v8::Value> removeEventListenerMethodCallback(const v8::Arguments& args)
{
    return TestEventTargetV8Internal::removeEventListenerMethod(args);
}

static v8::Handle<v8::Value> dispatchEventMethod(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    TestEventTarget* imp = V8TestEventTarget::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    V8TRYCATCH(Event*, evt, V8Event::HasInstance(args[0], args.GetIsolate()) ? V8Event::toNative(v8::Handle<v8::Object>::Cast(args[0])) : 0);
    bool result = imp->dispatchEvent(evt, ec);
    if (UNLIKELY(ec))
        goto fail;
    return v8Boolean(result, args.GetIsolate());
    }
    fail:
    return setDOMException(ec, args.GetIsolate());
}

static v8::Handle<v8::Value> dispatchEventMethodCallback(const v8::Arguments& args)
{
    return TestEventTargetV8Internal::dispatchEventMethod(args);
}

} // namespace TestEventTargetV8Internal

static const V8DOMConfiguration::BatchedMethod V8TestEventTargetMethods[] = {
    {"item", TestEventTargetV8Internal::itemMethodCallback},
    {"addEventListener", TestEventTargetV8Internal::addEventListenerMethodCallback},
    {"removeEventListener", TestEventTargetV8Internal::removeEventListenerMethodCallback},
};

static v8::Persistent<v8::FunctionTemplate> ConfigureV8TestEventTargetTemplate(v8::Persistent<v8::FunctionTemplate> desc, v8::Isolate* isolate)
{
    desc->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::configureTemplate(desc, "TestEventTarget", v8::Persistent<v8::FunctionTemplate>(), V8TestEventTarget::internalFieldCount,
        0, 0,
        V8TestEventTargetMethods, WTF_ARRAY_LENGTH(V8TestEventTargetMethods), isolate);
    UNUSED_PARAM(defaultSignature); // In some cases, it will not be used.
    v8::Local<v8::ObjectTemplate> instance = desc->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> proto = desc->PrototypeTemplate();
    UNUSED_PARAM(instance); // In some cases, it will not be used.
    UNUSED_PARAM(proto); // In some cases, it will not be used.
    
    setCollectionIndexedGetter<TestEventTarget, Node>(desc);
    desc->InstanceTemplate()->SetNamedPropertyHandler(V8TestEventTarget::namedPropertyGetter, 0, 0, 0, 0);
    desc->InstanceTemplate()->MarkAsUndetectable();

    // Custom Signature 'dispatchEvent'
    const int dispatchEventArgc = 1;
    v8::Handle<v8::FunctionTemplate> dispatchEventArgv[dispatchEventArgc] = { V8Event::GetRawTemplate(isolate) };
    v8::Handle<v8::Signature> dispatchEventSignature = v8::Signature::New(desc, dispatchEventArgc, dispatchEventArgv);
    proto->Set(v8::String::NewSymbol("dispatchEvent"), v8::FunctionTemplate::New(TestEventTargetV8Internal::dispatchEventMethodCallback, v8Undefined(), dispatchEventSignature));

    // Custom toString template
    desc->Set(v8::String::NewSymbol("toString"), V8PerIsolateData::current()->toStringTemplate());
    return desc;
}

v8::Persistent<v8::FunctionTemplate> V8TestEventTarget::GetRawTemplate(v8::Isolate* isolate)
{
    V8PerIsolateData* data = V8PerIsolateData::from(isolate);
    V8PerIsolateData::TemplateMap::iterator result = data->rawTemplateMap().find(&info);
    if (result != data->rawTemplateMap().end())
        return result->value;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ = createRawTemplate(isolate);
    data->rawTemplateMap().add(&info, templ);
    return templ;
}

v8::Persistent<v8::FunctionTemplate> V8TestEventTarget::GetTemplate(v8::Isolate* isolate)
{
    V8PerIsolateData* data = V8PerIsolateData::from(isolate);
    V8PerIsolateData::TemplateMap::iterator result = data->templateMap().find(&info);
    if (result != data->templateMap().end())
        return result->value;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ =
        ConfigureV8TestEventTargetTemplate(GetRawTemplate(isolate), isolate);
    data->templateMap().add(&info, templ);
    return templ;
}

bool V8TestEventTarget::HasInstance(v8::Handle<v8::Value> value, v8::Isolate* isolate)
{
    return GetRawTemplate(isolate)->HasInstance(value);
}

EventTarget* V8TestEventTarget::toEventTarget(v8::Handle<v8::Object> object)
{
    return toNative(object);
}


v8::Handle<v8::Object> V8TestEventTarget::createWrapper(PassRefPtr<TestEventTarget> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
{
    ASSERT(impl.get());
    ASSERT(DOMDataStore::getWrapper(impl.get(), isolate).IsEmpty());

#if ENABLE(BINDING_INTEGRITY)
    checkTypeOrDieTrying(impl.get());
#endif

    v8::Handle<v8::Object> wrapper = V8DOMWrapper::createWrapper(creationContext, &info, impl.get(), isolate);
    if (UNLIKELY(wrapper.IsEmpty()))
        return wrapper;

    installPerContextProperties(wrapper, impl.get(), isolate);
    V8DOMWrapper::associateObjectWithWrapper(impl, &info, wrapper, isolate, hasDependentLifetime ? WrapperConfiguration::Dependent : WrapperConfiguration::Independent);
    return wrapper;
}
void V8TestEventTarget::derefObject(void* object)
{
    static_cast<TestEventTarget*>(object)->deref();
}

} // namespace WebCore
