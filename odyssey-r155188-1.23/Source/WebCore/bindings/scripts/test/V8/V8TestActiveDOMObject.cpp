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
#include "V8TestActiveDOMObject.h"

#include "BindingState.h"
#include "ContextFeatures.h"
#include "ExceptionCode.h"
#include "Frame.h"
#include "RuntimeEnabledFeatures.h"
#include "V8Binding.h"
#include "V8DOMWrapper.h"
#include "V8Node.h"
#include <wtf/UnusedParam.h>

#if ENABLE(BINDING_INTEGRITY)
#if defined(OS_WIN)
#pragma warning(disable: 4483)
extern "C" { extern void (*const __identifier("??_7TestActiveDOMObject@WebCore@@6B@")[])(); }
#else
extern "C" { extern void* _ZTVN7WebCore19TestActiveDOMObjectE[]; }
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
inline void checkTypeOrDieTrying(TestActiveDOMObject* object)
{
    void* actualVTablePointer = *(reinterpret_cast<void**>(object));
#if defined(OS_WIN)
    void* expectedVTablePointer = reinterpret_cast<void*>(__identifier("??_7TestActiveDOMObject@WebCore@@6B@"));
#else
    void* expectedVTablePointer = &_ZTVN7WebCore19TestActiveDOMObjectE[2];
#endif
    if (actualVTablePointer != expectedVTablePointer)
        CRASH();
}
#endif // ENABLE(BINDING_INTEGRITY)

WrapperTypeInfo V8TestActiveDOMObject::info = { V8TestActiveDOMObject::GetTemplate, V8TestActiveDOMObject::derefObject, 0, 0, 0, V8TestActiveDOMObject::installPerContextPrototypeProperties, 0, WrapperTypeObjectPrototype };

namespace TestActiveDOMObjectV8Internal {

template <typename T> void V8_USE(T) { }

static v8::Handle<v8::Value> excitingAttrAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    TestActiveDOMObject* imp = V8TestActiveDOMObject::toNative(info.Holder());
    return v8Integer(imp->excitingAttr(), info.GetIsolate());
}

static v8::Handle<v8::Value> excitingAttrAttrGetterCallback(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    return TestActiveDOMObjectV8Internal::excitingAttrAttrGetter(name, info);
}

static v8::Handle<v8::Value> excitingFunctionMethod(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    TestActiveDOMObject* imp = V8TestActiveDOMObject::toNative(args.Holder());
    if (!BindingSecurity::shouldAllowAccessToFrame(BindingState::instance(), imp->frame()))
        return v8Undefined();
    V8TRYCATCH(Node*, nextChild, V8Node::HasInstance(args[0], args.GetIsolate()) ? V8Node::toNative(v8::Handle<v8::Object>::Cast(args[0])) : 0);
    imp->excitingFunction(nextChild);
    return v8Undefined();
}

static v8::Handle<v8::Value> excitingFunctionMethodCallback(const v8::Arguments& args)
{
    return TestActiveDOMObjectV8Internal::excitingFunctionMethod(args);
}

static v8::Handle<v8::Value> postMessageMethod(const v8::Arguments& args)
{
    if (args.Length() < 1)
        return throwNotEnoughArgumentsError(args.GetIsolate());
    TestActiveDOMObject* imp = V8TestActiveDOMObject::toNative(args.Holder());
    V8TRYCATCH_FOR_V8STRINGRESOURCE(V8StringResource<>, message, args[0]);
    imp->postMessage(message);
    return v8Undefined();
}

static v8::Handle<v8::Value> postMessageMethodCallback(const v8::Arguments& args)
{
    return TestActiveDOMObjectV8Internal::postMessageMethod(args);
}

static v8::Handle<v8::Value> postMessageAttrGetter(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    static v8::Persistent<v8::FunctionTemplate> privateTemplate = v8::Persistent<v8::FunctionTemplate>::New(info.GetIsolate(), v8::FunctionTemplate::New(TestActiveDOMObjectV8Internal::postMessageMethodCallback, v8Undefined(), v8::Signature::New(V8TestActiveDOMObject::GetRawTemplate(info.GetIsolate()))));
    v8::Handle<v8::Object> holder = info.This()->FindInstanceInPrototypeChain(V8TestActiveDOMObject::GetTemplate(info.GetIsolate()));
    if (holder.IsEmpty()) {
        // can only reach here by 'object.__proto__.func', and it should passed
        // domain security check already
        return privateTemplate->GetFunction();
    }
    TestActiveDOMObject* imp = V8TestActiveDOMObject::toNative(holder);
    if (!BindingSecurity::shouldAllowAccessToFrame(BindingState::instance(), imp->frame(), DoNotReportSecurityError)) {
        static v8::Persistent<v8::FunctionTemplate> sharedTemplate = v8::Persistent<v8::FunctionTemplate>::New(info.GetIsolate(), v8::FunctionTemplate::New(TestActiveDOMObjectV8Internal::postMessageMethodCallback, v8Undefined(), v8::Signature::New(V8TestActiveDOMObject::GetRawTemplate(info.GetIsolate()))));
        return sharedTemplate->GetFunction();
    }

    v8::Local<v8::Value> hiddenValue = info.This()->GetHiddenValue(name);
    if (!hiddenValue.IsEmpty())
        return hiddenValue;

    return privateTemplate->GetFunction();
}

static v8::Handle<v8::Value> postMessageAttrGetterCallback(v8::Local<v8::String> name, const v8::AccessorInfo& info)
{
    return TestActiveDOMObjectV8Internal::postMessageAttrGetter(name, info);
}

static void TestActiveDOMObjectDomainSafeFunctionSetter(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::AccessorInfo& info)
{
    v8::Handle<v8::Object> holder = info.This()->FindInstanceInPrototypeChain(V8TestActiveDOMObject::GetTemplate(info.GetIsolate()));
    if (holder.IsEmpty())
        return;
    TestActiveDOMObject* imp = V8TestActiveDOMObject::toNative(holder);
    if (!BindingSecurity::shouldAllowAccessToFrame(BindingState::instance(), imp->frame()))
        return;

    info.This()->SetHiddenValue(name, value);
}

} // namespace TestActiveDOMObjectV8Internal

static const V8DOMConfiguration::BatchedAttribute V8TestActiveDOMObjectAttrs[] = {
    // Attribute 'excitingAttr' (Type: 'readonly attribute' ExtAttr: '')
    {"excitingAttr", TestActiveDOMObjectV8Internal::excitingAttrAttrGetterCallback, 0, 0 /* no data */, static_cast<v8::AccessControl>(v8::DEFAULT), static_cast<v8::PropertyAttribute>(v8::None), 0 /* on instance */},
};

static v8::Persistent<v8::FunctionTemplate> ConfigureV8TestActiveDOMObjectTemplate(v8::Persistent<v8::FunctionTemplate> desc, v8::Isolate* isolate)
{
    desc->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = V8DOMConfiguration::configureTemplate(desc, "TestActiveDOMObject", v8::Persistent<v8::FunctionTemplate>(), V8TestActiveDOMObject::internalFieldCount,
        V8TestActiveDOMObjectAttrs, WTF_ARRAY_LENGTH(V8TestActiveDOMObjectAttrs),
        0, 0, isolate);
    UNUSED_PARAM(defaultSignature); // In some cases, it will not be used.
    v8::Local<v8::ObjectTemplate> instance = desc->InstanceTemplate();
    v8::Local<v8::ObjectTemplate> proto = desc->PrototypeTemplate();
    UNUSED_PARAM(instance); // In some cases, it will not be used.
    UNUSED_PARAM(proto); // In some cases, it will not be used.
    instance->SetAccessCheckCallbacks(V8TestActiveDOMObject::namedSecurityCheck, V8TestActiveDOMObject::indexedSecurityCheck, v8::External::New(&V8TestActiveDOMObject::info));

    // Custom Signature 'excitingFunction'
    const int excitingFunctionArgc = 1;
    v8::Handle<v8::FunctionTemplate> excitingFunctionArgv[excitingFunctionArgc] = { V8Node::GetRawTemplate(isolate) };
    v8::Handle<v8::Signature> excitingFunctionSignature = v8::Signature::New(desc, excitingFunctionArgc, excitingFunctionArgv);
    proto->Set(v8::String::NewSymbol("excitingFunction"), v8::FunctionTemplate::New(TestActiveDOMObjectV8Internal::excitingFunctionMethodCallback, v8Undefined(), excitingFunctionSignature));

    // Function 'postMessage' (ExtAttr: 'DoNotCheckSecurity')
    proto->SetAccessor(v8::String::NewSymbol("postMessage"), TestActiveDOMObjectV8Internal::postMessageAttrGetterCallback, TestActiveDOMObjectV8Internal::TestActiveDOMObjectDomainSafeFunctionSetter, v8Undefined(), v8::ALL_CAN_READ, static_cast<v8::PropertyAttribute>(v8::DontDelete));

    // Custom toString template
    desc->Set(v8::String::NewSymbol("toString"), V8PerIsolateData::current()->toStringTemplate());
    return desc;
}

v8::Persistent<v8::FunctionTemplate> V8TestActiveDOMObject::GetRawTemplate(v8::Isolate* isolate)
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

v8::Persistent<v8::FunctionTemplate> V8TestActiveDOMObject::GetTemplate(v8::Isolate* isolate)
{
    V8PerIsolateData* data = V8PerIsolateData::from(isolate);
    V8PerIsolateData::TemplateMap::iterator result = data->templateMap().find(&info);
    if (result != data->templateMap().end())
        return result->value;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ =
        ConfigureV8TestActiveDOMObjectTemplate(GetRawTemplate(isolate), isolate);
    data->templateMap().add(&info, templ);
    return templ;
}

bool V8TestActiveDOMObject::HasInstance(v8::Handle<v8::Value> value, v8::Isolate* isolate)
{
    return GetRawTemplate(isolate)->HasInstance(value);
}


v8::Handle<v8::Object> V8TestActiveDOMObject::createWrapper(PassRefPtr<TestActiveDOMObject> impl, v8::Handle<v8::Object> creationContext, v8::Isolate* isolate)
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
void V8TestActiveDOMObject::derefObject(void* object)
{
    static_cast<TestActiveDOMObject*>(object)->deref();
}

} // namespace WebCore
