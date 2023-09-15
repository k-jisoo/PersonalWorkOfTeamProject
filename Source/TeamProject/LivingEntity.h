// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "LivingEntity.generated.h"

// 이 인터페이스는 "UMyInterface"라는 이름으로 등록됩니다.
UINTERFACE(MinimalAPI)
class ULivingEntity : public UInterface
{
    GENERATED_BODY()
};

class TEAMPROJECT_API ILivingEntity
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyInterface")
    void DamageProcess();
};