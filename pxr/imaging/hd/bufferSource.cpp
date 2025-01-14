//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#include "pxr/imaging/hd/bufferSource.h"

#include "pxr/base/arch/hash.h"

PXR_NAMESPACE_OPEN_SCOPE

template <class HashState>
void
TfHashAppend(HashState &h, HdBufferSource const &bs)
{
    HdTupleType tt = bs.GetTupleType();
    h.AppendContiguous(reinterpret_cast<const char *>(bs.GetData()),
                       HdDataSizeOfTupleType(tt) * bs.GetNumElements());
    // Hash signature as well.
    h.Append(bs.GetName(), tt);
}

HdBufferSource::~HdBufferSource()
{
}

size_t
HdBufferSource::ComputeHash() const
{
    return TfHash()(*this);
}

bool
HdBufferSource::HasPreChainedBuffer() const
{
    return false;
}

HdBufferSourceSharedPtr
HdBufferSource::GetPreChainedBuffer() const
{
    return HdBufferSourceSharedPtr();
}

bool
HdBufferSource::HasChainedBuffer() const
{
    return false;
}

HdBufferSourceSharedPtrVector
HdBufferSource::GetChainedBuffers() const
{
    return HdBufferSourceSharedPtrVector();
}

bool
HdBufferSource::IsValid() const
{
    return _CheckValid();
}

// ---------------------------------------------------------------------------

size_t
HdComputedBufferSource::ComputeHash() const
{
    return 0;
}

TfToken const &
HdComputedBufferSource::GetName() const
{
    if (!_result) {
        static TfToken empty;
        return empty;
    }
    return _result->GetName();
}

void const*
HdComputedBufferSource::GetData() const
{
    if (!_result) {
        TF_CODING_ERROR("HdComputedBufferSource::GetData() called without "
                        "setting the result.");
        return nullptr;
    }
    return _result->GetData();
}

HdTupleType
HdComputedBufferSource::GetTupleType() const
{
    if (!_result) {
        TF_CODING_ERROR("HdComputedBufferSource::GetTupleType() called "
                        "without setting the result.");
        return {HdTypeInvalid, 0};
    }
    return _result->GetTupleType();
}

size_t
HdComputedBufferSource::GetNumElements() const
{
    // GetNumElements returns 0 for the empty result.
    return _result ? _result->GetNumElements() : 0;
}

// ---------------------------------------------------------------------------

size_t
HdNullBufferSource::ComputeHash() const
{
    return 0;
}

TfToken const &
HdNullBufferSource::GetName() const
{
    TF_CODING_ERROR("HdNullBufferSource can't be scheduled with a buffer range");
    static TfToken empty;
    return empty;
}

void const*
HdNullBufferSource::GetData() const
{
    TF_CODING_ERROR("HdNullBufferSource can't be scheduled with a buffer range");
    return nullptr;
}

HdTupleType
HdNullBufferSource::GetTupleType() const
{
    TF_CODING_ERROR("HdNullBufferSource can't be scheduled with a buffer "
                    "range");
    return {HdTypeInvalid, 0};
}

size_t
HdNullBufferSource::GetNumElements() const
{
    return 0;
}

void
HdNullBufferSource::GetBufferSpecs(HdBufferSpecVector *specs) const
{
    // nothing
}

PXR_NAMESPACE_CLOSE_SCOPE

