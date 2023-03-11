// Fill out your copyright notice in the Description page of Project Settings.


#include "UnrealGrpcHelloWorldProto.h"

UUnrealGrpcHelloWorldProto::UUnrealGrpcHelloWorldProto(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	
}

void UUnrealGrpcHelloWorldProto::NewStub(const FString& InChannel)
{
	AsyncTask(ENamedThreads::AnyThread, [this, &InChannel]()
	{
		std::string EndPoint =  TCHAR_TO_UTF8(*InChannel);
    	auto Channel = grpc::CreateChannel(EndPoint, grpc::InsecureChannelCredentials());
    	stub_ = helloworld::Greeter::NewStub(Channel);	
	});
}

void UUnrealGrpcHelloWorldProto::SayHello()
{
	helloworld::HelloRequest Request;

	std::string name = "hazuki";
	
	Request.set_name(name);
	
	helloworld::HelloReply Reply;

	grpc::ClientContext Context;
	
	grpc::Status Status = stub_->SayHello(&Context, Request, &Reply);

	std::string reply_message;
	
	if (Status.ok())
	{
		reply_message =  Reply.message();
	}
	else
	{
		
	}
}


