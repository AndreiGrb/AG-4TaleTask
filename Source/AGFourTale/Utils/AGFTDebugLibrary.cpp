#include "AGFTDebugLibrary.h"

#if ENABLE_DRAW_DEBUG
	#include "DrawDebugHelpers.h"
#endif

#if ENABLE_DRAW_DEBUG
	static constexpr float TRACE_DEBUG_IMPACTPOINT_SIZE = 16.f;
#endif


/** Util for drawing result of single line trace  */
void FAGFTDebugTrace::DrawDebugLineTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, bool bHit, const FHitResult& OutHit, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	// @fixme, draw line with thickness = 2.f?
	if (bHit && OutHit.bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		::DrawDebugLine(World, Start, OutHit.ImpactPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, OutHit.ImpactPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugPoint(World, OutHit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		::DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

/** Util for drawing result of multi line trace  */
void FAGFTDebugTrace::DrawDebugLineTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	// @fixme, draw line with thickness = 2.f?
	if (bHit && OutHits.Last().bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		FVector const BlockingHitPoint = OutHits.Last().ImpactPoint;
		::DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		::DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}

	// draw hits
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugBoxTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, bool bHit, const FHitResult& OutHit, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHit.bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		DrawDebugSweptBox(World, Start, OutHit.Location, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
		DrawDebugSweptBox(World, OutHit.Location, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugPoint(World, OutHit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugSweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugBoxTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, const FVector& HalfSize, const FRotator& Orientation, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHits.Last().bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		FVector const BlockingHitPoint = OutHits.Last().Location;
		DrawDebugSweptBox(World, Start, BlockingHitPoint, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
		DrawDebugSweptBox(World, BlockingHitPoint, End, Orientation, HalfSize, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugSweptBox(World, Start, End, Orientation, HalfSize, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}

	// draw hits
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugSphereTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, bool bHit, const FHitResult& OutHit, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHit.bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		DrawDebugSweptSphere(World, Start, OutHit.Location, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
		DrawDebugSweptSphere(World, OutHit.Location, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugPoint(World, OutHit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugSweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugSphereTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHits.Last().bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		FVector const BlockingHitPoint = OutHits.Last().Location;
		DrawDebugSweptSphere(World, Start, BlockingHitPoint, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
		DrawDebugSweptSphere(World, BlockingHitPoint, End, Radius, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		DrawDebugSweptSphere(World, Start, End, Radius, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}

	// draw hits
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugCapsuleTraceSingle(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, bool bHit, const FHitResult& OutHit, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHit.bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		::DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugCapsule(World, OutHit.Location, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, Start, OutHit.Location, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugPoint(World, OutHit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, TraceColor.ToFColor(true), bPersistent, LifeTime);

		::DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, OutHit.Location, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		::DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

void FAGFTDebugTrace::DrawDebugCapsuleTraceMulti(const UWorld* World, const FVector& Start, const FVector& End, float Radius, float HalfHeight, bool bHit, const TArray<FHitResult>& OutHits, float DrawTime, FLinearColor TraceColor, FLinearColor TraceHitColor)
{
#if ENABLE_DRAW_DEBUG
	const bool bPersistent = DrawTime < 0.f;
	const float LifeTime = DrawTime;

	if (bHit && OutHits.Last().bBlockingHit)
	{
		// Red up to the blocking hit, green thereafter
		FVector const BlockingHitPoint = OutHits.Last().Location;
		::DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugCapsule(World, BlockingHitPoint, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, Start, BlockingHitPoint, TraceColor.ToFColor(true), bPersistent, LifeTime);

		::DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, BlockingHitPoint, End, TraceHitColor.ToFColor(true), bPersistent, LifeTime);
	}
	else
	{
		// no hit means all red
		::DrawDebugCapsule(World, Start, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugCapsule(World, End, HalfHeight, Radius, FQuat::Identity, TraceColor.ToFColor(true), bPersistent, LifeTime);
		::DrawDebugLine(World, Start, End, TraceColor.ToFColor(true), bPersistent, LifeTime);
	}

	// draw hits
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, TRACE_DEBUG_IMPACTPOINT_SIZE, (Hit.bBlockingHit ? TraceColor.ToFColor(true) : TraceHitColor.ToFColor(true)), bPersistent, LifeTime);
	}
#endif // ENABLE_DRAW_DEBUG
}

#if ENABLE_DRAW_DEBUG
void FAGFTDebugTrace::DrawDebugSweptSphere(const UWorld* InWorld, const FVector& Start, const FVector& End, float Radius, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
{
	FVector const TraceVec = End - Start;
	float const Dist = TraceVec.Size();

	FVector const Center = Start + TraceVec * 0.5f;
	float const HalfHeight = (Dist * 0.5f) + Radius;

	FQuat const CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	::DrawDebugCapsule(InWorld, Center, HalfHeight, Radius, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
}
#endif // ENABLE_DRAW_DEBUG

#if ENABLE_DRAW_DEBUG
void FAGFTDebugTrace::DrawDebugSweptBox(const UWorld* InWorld, const FVector& Start, const FVector& End, const FRotator& Orientation, const FVector& HalfSize, const FColor& Color, bool bPersistentLines, float LifeTime, uint8 DepthPriority)
{
	FVector const TraceVec = End - Start;

	FQuat const CapsuleRot = Orientation.Quaternion();
	::DrawDebugBox(InWorld, Start, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);

	//now draw lines from vertices
	FVector Vertices[8];
	Vertices[0] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//flt
	Vertices[1] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, HalfSize.Y, -HalfSize.Z));	//frt
	Vertices[2] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, -HalfSize.Y, HalfSize.Z));	//flb
	Vertices[3] = Start + CapsuleRot.RotateVector(FVector(-HalfSize.X, HalfSize.Y, HalfSize.Z));	//frb
	Vertices[4] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, -HalfSize.Y, -HalfSize.Z));	//blt
	Vertices[5] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, HalfSize.Y, -HalfSize.Z));	//brt
	Vertices[6] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, -HalfSize.Y, HalfSize.Z));	//blb
	Vertices[7] = Start + CapsuleRot.RotateVector(FVector(HalfSize.X, HalfSize.Y, HalfSize.Z));		//brb
	for (int32 VertexIdx = 0; VertexIdx < 8; ++VertexIdx)
	{
		::DrawDebugLine(InWorld, Vertices[VertexIdx], Vertices[VertexIdx] + TraceVec, Color, bPersistentLines, LifeTime, DepthPriority);
	}

	::DrawDebugBox(InWorld, End, HalfSize, CapsuleRot, Color, bPersistentLines, LifeTime, DepthPriority);
}
#endif // ENABLE_DRAW_DEBUG
