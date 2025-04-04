// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CustomAbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
//UCLASS(BlueprintType)
class BMODULARTEMP_API UCustomAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

	virtual void NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle, UGameplayAbility* Ability) override;

	// Custom code removing tags within a category
	UFUNCTION(BlueprintCallable)
	void RemoveTagsInCategory(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayTag ParentTag);

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_NotifyTagsRemoved(UAbilitySystemComponent* AbilitySystemComponent, const TArray<FGameplayTag>& TagsToRemove);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_ApplyCooldownByTag(const FGameplayTag TagToUse);

	UFUNCTION(Client, Reliable, BlueprintCallable)
	void Client_ApplyCooldownByTag(const FGameplayTag TagToUse);
	
public:
	UFUNCTION(BlueprintCallable)
	void AddCustomTag(FGameplayTag NewTag);
};
