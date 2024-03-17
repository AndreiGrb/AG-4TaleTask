#pragma once

struct FAGFTDebugTrace
{
public:
	static void DrawDebugLineTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, bool bHit, const FHitResult& OutHit, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);
	static void DrawDebugLineTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);

	static void DrawDebugBoxTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, bool bHit, const FHitResult& OutHit, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);
	static void DrawDebugBoxTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);

	static void DrawDebugSphereTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, bool bHit, const FHitResult& OutHit, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);
	static void DrawDebugSphereTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);

	static void DrawDebugCapsuleTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, bool bHit, const FHitResult& OutHit, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);
	static void DrawDebugCapsuleTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime = 0.f, FLinearColor TraceColor = FLinearColor::Red, FLinearColor TraceHitColor = FLinearColor::Green);
	
private:
#if ENABLE_DRAW_DEBUG
	static void DrawDebugSweptSphere(const UWorld* InWorld, FVector const& Start, FVector const& End, float Radius, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
	static void DrawDebugSweptBox(const UWorld* InWorld, FVector const& Start, FVector const& End, FRotator const & Orientation, FVector const & HalfSize, FColor const& Color, bool bPersistentLines = false, float LifeTime = -1.f, uint8 DepthPriority = 0);
#endif // ENABLE_DRAW_DEBUG
};