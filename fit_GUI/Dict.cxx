// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME Dict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "./inc/fit.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void delete_fit(void *p);
   static void deleteArray_fit(void *p);
   static void destruct_fit(void *p);
   static void streamer_fit(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::fit*)
   {
      ::fit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::fit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("fit", ::fit::Class_Version(), "inc/fit.h", 50,
                  typeid(::fit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::fit::Dictionary, isa_proxy, 16,
                  sizeof(::fit) );
      instance.SetDelete(&delete_fit);
      instance.SetDeleteArray(&deleteArray_fit);
      instance.SetDestructor(&destruct_fit);
      instance.SetStreamerFunc(&streamer_fit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::fit*)
   {
      return GenerateInitInstanceLocal((::fit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::fit*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr fit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *fit::Class_Name()
{
   return "fit";
}

//______________________________________________________________________________
const char *fit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int fit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::fit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *fit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *fit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::fit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void fit::Streamer(TBuffer &R__b)
{
   // Stream an object of class fit.

   ::Error("fit::Streamer", "version id <=0 in ClassDef, dummy Streamer() called"); if (R__b.IsReading()) { }
}

namespace ROOT {
   // Wrapper around operator delete
   static void delete_fit(void *p) {
      delete ((::fit*)p);
   }
   static void deleteArray_fit(void *p) {
      delete [] ((::fit*)p);
   }
   static void destruct_fit(void *p) {
      typedef ::fit current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_fit(TBuffer &buf, void *obj) {
      ((::fit*)obj)->::fit::Streamer(buf);
   }
} // end of namespace ROOT for class ::fit

namespace {
  void TriggerDictionaryInitialization_Dict_Impl() {
    static const char* headers[] = {
"./inc/fit.h",
0
    };
    static const char* includePaths[] = {
"/home/alejandro/build/include",
"/home/alejandro/Development/CMS/fit_GUI/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "Dict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$./inc/fit.h")))  fit;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "Dict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "./inc/fit.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"fit", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("Dict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_Dict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_Dict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_Dict() {
  TriggerDictionaryInitialization_Dict_Impl();
}
