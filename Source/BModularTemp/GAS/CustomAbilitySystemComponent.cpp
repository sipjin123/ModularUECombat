// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomAbilitySystemComponent.h"


void UCustomAbilitySystemComponent::NotifyAbilityActivated(const FGameplayAbilitySpecHandle Handle,
	UGameplayAbility* Ability)
{
	bool NewVal = HasMatchingGameplayTag(FGameplayTag::RequestGameplayTag(FName("Status.Invulnerable")));
	if (GetOwner()->HasAuthority())
	{
		// Do logic here for when invulnerability ends
		UE_LOG(LogTemp, Warning, TEXT("An Ability has Ended! %d"), NewVal ? 1 : 0);
	}
	
	Super::NotifyAbilityActivated(Handle, Ability);
}

void UCustomAbilitySystemComponent::RemoveTagsInCategory(UAbilitySystemComponent* AbilitySystemComponent,
	const FGameplayTag ParentTag)
{
	if (!AbilitySystemComponent) return;

	FGameplayTagContainer OwnedTags;
	AbilitySystemComponent->GetOwnedGameplayTags(OwnedTags);

	TArray<FGameplayTag> TagsToRemove;
	for (const FGameplayTag& Tag : OwnedTags)
	{
		if (Tag.MatchesTag(ParentTag))  // Check if the tag is within the subcategory
		{
			TagsToRemove.Add(Tag);
		}
	}

	for (const FGameplayTag& Tag : TagsToRemove)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
		
		// Notify all clients to sync tag removal
		Multicast_NotifyTagsRemoved(AbilitySystemComponent, TagsToRemove);
	}
}

void UCustomAbilitySystemComponent::Server_ApplyCooldownByTag_Implementation(const FGameplayTag TagToUse)
{
	Client_ApplyCooldownByTag_Implementation(TagToUse);
}

void UCustomAbilitySystemComponent::Client_ApplyCooldownByTag_Implementation(const FGameplayTag TagToUse)
{
	AddLooseGameplayTag(TagToUse);
}

void UCustomAbilitySystemComponent::Multicast_NotifyTagsRemoved_Implementation(UAbilitySystemComponent* AbilitySystemComponent, const TArray<FGameplayTag>& TagsToRemove)
{
	if (!AbilitySystemComponent) return;

	for (const FGameplayTag& Tag : TagsToRemove)
	{
		AbilitySystemComponent->RemoveLooseGameplayTag(Tag);
	}
}

