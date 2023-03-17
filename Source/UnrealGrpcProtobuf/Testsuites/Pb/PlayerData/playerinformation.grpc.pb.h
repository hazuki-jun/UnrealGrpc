// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: playerinformation.proto
// Original file comments:
// Copyright 2015 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
#ifndef GRPC_playerinformation_2eproto__INCLUDED
#define GRPC_playerinformation_2eproto__INCLUDED

#include "playerinformation.pb.h"

#include <functional>
#include <grpc/impl/codegen/port_platform.h>
#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/client_callback.h>
#include <grpcpp/impl/codegen/client_context.h>
#include <grpcpp/impl/codegen/completion_queue.h>
#include <grpcpp/impl/codegen/message_allocator.h>
#include <grpcpp/impl/codegen/method_handler.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/server_callback.h>
#include <grpcpp/impl/codegen/server_callback_handlers.h>
#include <grpcpp/impl/codegen/server_context.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace PlayerInformation {

// The greeting service definition.
class Greeter final {
 public:
  static constexpr char const* service_full_name() {
    return "PlayerInformation.Greeter";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Sends a greeting
    virtual ::grpc::Status GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::PlayerInformation::Information* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>> AsyncGetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>>(AsyncGetInformationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>> PrepareAsyncGetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>>(PrepareAsyncGetInformationRaw(context, request, cq));
    }
    virtual ::grpc::Status SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::PlayerInformation::SetInformationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>> AsyncSetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>>(AsyncSetInformationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>> PrepareAsyncSetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>>(PrepareAsyncSetInformationRaw(context, request, cq));
    }
    class experimental_async_interface {
     public:
      virtual ~experimental_async_interface() {}
      // Sends a greeting
      virtual void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
      virtual void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, std::function<void(::grpc::Status)>) = 0;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      virtual void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, ::grpc::ClientUnaryReactor* reactor) = 0;
      #else
      virtual void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) = 0;
      #endif
    };
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    typedef class experimental_async_interface async_interface;
    #endif
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    async_interface* async() { return experimental_async(); }
    #endif
    virtual class experimental_async_interface* experimental_async() { return nullptr; }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>* AsyncGetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::Information>* PrepareAsyncGetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>* AsyncSetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::PlayerInformation::SetInformationReply>* PrepareAsyncSetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::PlayerInformation::Information* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>> AsyncGetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>>(AsyncGetInformationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>> PrepareAsyncGetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>>(PrepareAsyncGetInformationRaw(context, request, cq));
    }
    ::grpc::Status SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::PlayerInformation::SetInformationReply* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>> AsyncSetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>>(AsyncSetInformationRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>> PrepareAsyncSetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>>(PrepareAsyncSetInformationRaw(context, request, cq));
    }
    class experimental_async final :
      public StubInterface::experimental_async_interface {
     public:
      void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void GetInformation(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
      void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, std::function<void(::grpc::Status)>) override;
      #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, ::grpc::ClientUnaryReactor* reactor) override;
      #else
      void SetInformation(::grpc::ClientContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response, ::grpc::experimental::ClientUnaryReactor* reactor) override;
      #endif
     private:
      friend class Stub;
      explicit experimental_async(Stub* stub): stub_(stub) { }
      Stub* stub() { return stub_; }
      Stub* stub_;
    };
    class experimental_async_interface* experimental_async() override { return &async_stub_; }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    class experimental_async async_stub_{this};
    ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>* AsyncGetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::PlayerInformation::Information>* PrepareAsyncGetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::GetInformationRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>* AsyncSetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::PlayerInformation::SetInformationReply>* PrepareAsyncSetInformationRaw(::grpc::ClientContext* context, const ::PlayerInformation::Information& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_GetInformation_;
    const ::grpc::internal::RpcMethod rpcmethod_SetInformation_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Sends a greeting
    virtual ::grpc::Status GetInformation(::grpc::ServerContext* context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response);
    virtual ::grpc::Status SetInformation(::grpc::ServerContext* context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_GetInformation() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetInformation(::grpc::ServerContext* context, ::PlayerInformation::GetInformationRequest* request, ::grpc::ServerAsyncResponseWriter< ::PlayerInformation::Information>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithAsyncMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithAsyncMethod_SetInformation() {
      ::grpc::Service::MarkMethodAsync(1);
    }
    ~WithAsyncMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSetInformation(::grpc::ServerContext* context, ::PlayerInformation::Information* request, ::grpc::ServerAsyncResponseWriter< ::PlayerInformation::SetInformationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_GetInformation<WithAsyncMethod_SetInformation<Service > > AsyncService;
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_GetInformation() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::PlayerInformation::GetInformationRequest, ::PlayerInformation::Information>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::PlayerInformation::GetInformationRequest* request, ::PlayerInformation::Information* response) { return this->GetInformation(context, request, response); }));}
    void SetMessageAllocatorFor_GetInformation(
        ::grpc::experimental::MessageAllocator< ::PlayerInformation::GetInformationRequest, ::PlayerInformation::Information>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(0);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(0);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::PlayerInformation::GetInformationRequest, ::PlayerInformation::Information>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetInformation(
      ::grpc::CallbackServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetInformation(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithCallbackMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithCallbackMethod_SetInformation() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::PlayerInformation::Information, ::PlayerInformation::SetInformationReply>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::PlayerInformation::Information* request, ::PlayerInformation::SetInformationReply* response) { return this->SetInformation(context, request, response); }));}
    void SetMessageAllocatorFor_SetInformation(
        ::grpc::experimental::MessageAllocator< ::PlayerInformation::Information, ::PlayerInformation::SetInformationReply>* allocator) {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::GetHandler(1);
    #else
      ::grpc::internal::MethodHandler* const handler = ::grpc::Service::experimental().GetHandler(1);
    #endif
      static_cast<::grpc::internal::CallbackUnaryHandler< ::PlayerInformation::Information, ::PlayerInformation::SetInformationReply>*>(handler)
              ->SetMessageAllocator(allocator);
    }
    ~ExperimentalWithCallbackMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* SetInformation(
      ::grpc::CallbackServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* SetInformation(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/)
    #endif
      { return nullptr; }
  };
  #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
  typedef ExperimentalWithCallbackMethod_GetInformation<ExperimentalWithCallbackMethod_SetInformation<Service > > CallbackService;
  #endif

  typedef ExperimentalWithCallbackMethod_GetInformation<ExperimentalWithCallbackMethod_SetInformation<Service > > ExperimentalCallbackService;
  template <class BaseClass>
  class WithGenericMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_GetInformation() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithGenericMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithGenericMethod_SetInformation() {
      ::grpc::Service::MarkMethodGeneric(1);
    }
    ~WithGenericMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_GetInformation() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestGetInformation(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithRawMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithRawMethod_SetInformation() {
      ::grpc::Service::MarkMethodRaw(1);
    }
    ~WithRawMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestSetInformation(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(1, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_GetInformation() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(0,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->GetInformation(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* GetInformation(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* GetInformation(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class ExperimentalWithRawCallbackMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    ExperimentalWithRawCallbackMethod_SetInformation() {
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
      ::grpc::Service::
    #else
      ::grpc::Service::experimental().
    #endif
        MarkMethodRawCallback(1,
          new ::grpc::internal::CallbackUnaryHandler< ::grpc::ByteBuffer, ::grpc::ByteBuffer>(
            [this](
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
                   ::grpc::CallbackServerContext*
    #else
                   ::grpc::experimental::CallbackServerContext*
    #endif
                     context, const ::grpc::ByteBuffer* request, ::grpc::ByteBuffer* response) { return this->SetInformation(context, request, response); }));
    }
    ~ExperimentalWithRawCallbackMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    #ifdef GRPC_CALLBACK_API_NONEXPERIMENTAL
    virtual ::grpc::ServerUnaryReactor* SetInformation(
      ::grpc::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #else
    virtual ::grpc::experimental::ServerUnaryReactor* SetInformation(
      ::grpc::experimental::CallbackServerContext* /*context*/, const ::grpc::ByteBuffer* /*request*/, ::grpc::ByteBuffer* /*response*/)
    #endif
      { return nullptr; }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_GetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_GetInformation() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler<
          ::PlayerInformation::GetInformationRequest, ::PlayerInformation::Information>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::PlayerInformation::GetInformationRequest, ::PlayerInformation::Information>* streamer) {
                       return this->StreamedGetInformation(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_GetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status GetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::GetInformationRequest* /*request*/, ::PlayerInformation::Information* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedGetInformation(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::PlayerInformation::GetInformationRequest,::PlayerInformation::Information>* server_unary_streamer) = 0;
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_SetInformation : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service* /*service*/) {}
   public:
    WithStreamedUnaryMethod_SetInformation() {
      ::grpc::Service::MarkMethodStreamed(1,
        new ::grpc::internal::StreamedUnaryHandler<
          ::PlayerInformation::Information, ::PlayerInformation::SetInformationReply>(
            [this](::grpc::ServerContext* context,
                   ::grpc::ServerUnaryStreamer<
                     ::PlayerInformation::Information, ::PlayerInformation::SetInformationReply>* streamer) {
                       return this->StreamedSetInformation(context,
                         streamer);
                  }));
    }
    ~WithStreamedUnaryMethod_SetInformation() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status SetInformation(::grpc::ServerContext* /*context*/, const ::PlayerInformation::Information* /*request*/, ::PlayerInformation::SetInformationReply* /*response*/) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedSetInformation(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::PlayerInformation::Information,::PlayerInformation::SetInformationReply>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_GetInformation<WithStreamedUnaryMethod_SetInformation<Service > > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_GetInformation<WithStreamedUnaryMethod_SetInformation<Service > > StreamedService;
};

}  // namespace PlayerInformation


#endif  // GRPC_playerinformation_2eproto__INCLUDED
