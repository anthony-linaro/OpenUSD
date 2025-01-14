//
// Copyright 2016 Pixar
//
// Licensed under the terms set forth in the LICENSE.txt file available at
// https://openusd.org/license.
//
#ifndef USDGEOM_GENERATED_CAMERA_H
#define USDGEOM_GENERATED_CAMERA_H

/// \file usdGeom/camera.h

#include "pxr/pxr.h"
#include "pxr/usd/usdGeom/api.h"
#include "pxr/usd/usdGeom/xformable.h"
#include "pxr/usd/usd/prim.h"
#include "pxr/usd/usd/stage.h"
#include "pxr/usd/usdGeom/tokens.h"

#include "pxr/base/gf/camera.h" 

#include "pxr/base/vt/value.h"

#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/base/gf/matrix4d.h"

#include "pxr/base/tf/token.h"
#include "pxr/base/tf/type.h"

PXR_NAMESPACE_OPEN_SCOPE

class SdfAssetPath;

// -------------------------------------------------------------------------- //
// CAMERA                                                                     //
// -------------------------------------------------------------------------- //

/// \class UsdGeomCamera
///
/// Transformable camera.
/// 
/// Describes optical properties of a camera via a common set of attributes
/// that provide control over the camera's frustum as well as its depth of
/// field. For stereo, the left and right camera are individual prims tagged
/// through the \ref UsdGeomCamera::GetStereoRoleAttr() "stereoRole attribute".
/// 
/// There is a corresponding class GfCamera, which can hold the state of a
/// camera (at a particular time). \ref UsdGeomCamera::GetCamera() and
/// \ref UsdGeomCamera::SetFromCamera() convert between a USD camera prim and
/// a GfCamera.
/// 
/// To obtain the camera's location in world space, call the following on a
/// UsdGeomCamera 'camera':
/// \code
/// GfMatrix4d camXform = camera.ComputeLocalToWorldTransform(time);
/// \endcode
/// \note
/// <b>Cameras in USD are always "Y up", regardless of the stage's orientation
/// (i.e. UsdGeomGetStageUpAxis()).</b> 'camXform' positions the camera in the 
/// world, and the inverse transforms the world such that the camera is at the 
/// origin, looking down the -Z axis, with +Y as the up axis, and +X pointing to 
/// the right. This describes a __right handed coordinate system__. 
/// 
/// \section UsdGeom_CameraUnits Units of Measure for Camera Properties
/// 
/// Despite the familiarity of millimeters for specifying some physical
/// camera properties, UsdGeomCamera opts for greater consistency with all
/// other UsdGeom schemas, which measure geometric properties in scene units,
/// as determined by UsdGeomGetStageMetersPerUnit().  We do make a
/// concession, however, in that lens and filmback properties are measured in
/// __tenths of a scene unit__ rather than "raw" scene units.  This means
/// that with the fallback value of .01 for _metersPerUnit_ - i.e. scene unit
/// of centimeters - then these "tenth of scene unit" properties are
/// effectively millimeters.
/// 
/// \note If one adds a Camera prim to a UsdStage whose scene unit is not
/// centimeters, the fallback values for filmback properties will be
/// incorrect (or at the least, unexpected) in an absolute sense; however,
/// proper imaging through a "default camera" with focusing disabled depends
/// only on ratios of the other properties, so the camera is still usable.
/// However, it follows that if even one property is authored in the correct
/// scene units, then they all must be.
/// 
/// 
/// \sa \ref UsdGeom_LinAlgBasics
/// 
///
/// For any described attribute \em Fallback \em Value or \em Allowed \em Values below
/// that are text/tokens, the actual token is published and defined in \ref UsdGeomTokens.
/// So to set an attribute to the value "rightHanded", use UsdGeomTokens->rightHanded
/// as the value.
///
class UsdGeomCamera : public UsdGeomXformable
{
public:
    /// Compile time constant representing what kind of schema this class is.
    ///
    /// \sa UsdSchemaKind
    static const UsdSchemaKind schemaKind = UsdSchemaKind::ConcreteTyped;

    /// Construct a UsdGeomCamera on UsdPrim \p prim .
    /// Equivalent to UsdGeomCamera::Get(prim.GetStage(), prim.GetPath())
    /// for a \em valid \p prim, but will not immediately throw an error for
    /// an invalid \p prim
    explicit UsdGeomCamera(const UsdPrim& prim=UsdPrim())
        : UsdGeomXformable(prim)
    {
    }

    /// Construct a UsdGeomCamera on the prim held by \p schemaObj .
    /// Should be preferred over UsdGeomCamera(schemaObj.GetPrim()),
    /// as it preserves SchemaBase state.
    explicit UsdGeomCamera(const UsdSchemaBase& schemaObj)
        : UsdGeomXformable(schemaObj)
    {
    }

    /// Destructor.
    USDGEOM_API
    virtual ~UsdGeomCamera();

    /// Return a vector of names of all pre-declared attributes for this schema
    /// class and all its ancestor classes.  Does not include attributes that
    /// may be authored by custom/extended methods of the schemas involved.
    USDGEOM_API
    static const TfTokenVector &
    GetSchemaAttributeNames(bool includeInherited=true);

    /// Return a UsdGeomCamera holding the prim adhering to this
    /// schema at \p path on \p stage.  If no prim exists at \p path on
    /// \p stage, or if the prim at that path does not adhere to this schema,
    /// return an invalid schema object.  This is shorthand for the following:
    ///
    /// \code
    /// UsdGeomCamera(stage->GetPrimAtPath(path));
    /// \endcode
    ///
    USDGEOM_API
    static UsdGeomCamera
    Get(const UsdStagePtr &stage, const SdfPath &path);

    /// Attempt to ensure a \a UsdPrim adhering to this schema at \p path
    /// is defined (according to UsdPrim::IsDefined()) on this stage.
    ///
    /// If a prim adhering to this schema at \p path is already defined on this
    /// stage, return that prim.  Otherwise author an \a SdfPrimSpec with
    /// \a specifier == \a SdfSpecifierDef and this schema's prim type name for
    /// the prim at \p path at the current EditTarget.  Author \a SdfPrimSpec s
    /// with \p specifier == \a SdfSpecifierDef and empty typeName at the
    /// current EditTarget for any nonexistent, or existing but not \a Defined
    /// ancestors.
    ///
    /// The given \a path must be an absolute prim path that does not contain
    /// any variant selections.
    ///
    /// If it is impossible to author any of the necessary PrimSpecs, (for
    /// example, in case \a path cannot map to the current UsdEditTarget's
    /// namespace) issue an error and return an invalid \a UsdPrim.
    ///
    /// Note that this method may return a defined prim whose typeName does not
    /// specify this schema class, in case a stronger typeName opinion overrides
    /// the opinion at the current EditTarget.
    ///
    USDGEOM_API
    static UsdGeomCamera
    Define(const UsdStagePtr &stage, const SdfPath &path);

protected:
    /// Returns the kind of schema this class belongs to.
    ///
    /// \sa UsdSchemaKind
    USDGEOM_API
    UsdSchemaKind _GetSchemaKind() const override;

private:
    // needs to invoke _GetStaticTfType.
    friend class UsdSchemaRegistry;
    USDGEOM_API
    static const TfType &_GetStaticTfType();

    static bool _IsTypedSchema();

    // override SchemaBase virtuals.
    USDGEOM_API
    const TfType &_GetTfType() const override;

public:
    // --------------------------------------------------------------------- //
    // PROJECTION 
    // --------------------------------------------------------------------- //
    /// 
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `token projection = "perspective"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref UsdGeomTokens "Allowed Values" | perspective, orthographic |
    USDGEOM_API
    UsdAttribute GetProjectionAttr() const;

    /// See GetProjectionAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateProjectionAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // HORIZONTALAPERTURE 
    // --------------------------------------------------------------------- //
    /// Horizontal aperture in tenths of a scene unit; see 
    /// \ref UsdGeom_CameraUnits . Default is the equivalent of 
    /// the standard 35mm spherical projector aperture.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float horizontalAperture = 20.955` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetHorizontalApertureAttr() const;

    /// See GetHorizontalApertureAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateHorizontalApertureAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VERTICALAPERTURE 
    // --------------------------------------------------------------------- //
    /// Vertical aperture in tenths of a scene unit; see 
    /// \ref UsdGeom_CameraUnits . Default is the equivalent of 
    /// the standard 35mm spherical projector aperture.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float verticalAperture = 15.2908` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetVerticalApertureAttr() const;

    /// See GetVerticalApertureAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateVerticalApertureAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // HORIZONTALAPERTUREOFFSET 
    // --------------------------------------------------------------------- //
    /// Horizontal aperture offset in the same units as
    /// horizontalAperture. Defaults to 0.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float horizontalApertureOffset = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetHorizontalApertureOffsetAttr() const;

    /// See GetHorizontalApertureOffsetAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateHorizontalApertureOffsetAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // VERTICALAPERTUREOFFSET 
    // --------------------------------------------------------------------- //
    /// Vertical aperture offset in the same units as
    /// verticalAperture. Defaults to 0.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float verticalApertureOffset = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetVerticalApertureOffsetAttr() const;

    /// See GetVerticalApertureOffsetAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateVerticalApertureOffsetAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FOCALLENGTH 
    // --------------------------------------------------------------------- //
    /// Perspective focal length in tenths of a scene unit; see 
    /// \ref UsdGeom_CameraUnits .
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float focalLength = 50` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetFocalLengthAttr() const;

    /// See GetFocalLengthAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateFocalLengthAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // CLIPPINGRANGE 
    // --------------------------------------------------------------------- //
    /// Near and far clipping distances in scene units; see 
    /// \ref UsdGeom_CameraUnits .
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float2 clippingRange = (1, 1000000)` |
    /// | C++ Type | GfVec2f |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float2 |
    USDGEOM_API
    UsdAttribute GetClippingRangeAttr() const;

    /// See GetClippingRangeAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateClippingRangeAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // CLIPPINGPLANES 
    // --------------------------------------------------------------------- //
    /// Additional, arbitrarily oriented clipping planes.
    /// A vector (a,b,c,d) encodes a clipping plane that cuts off
    /// (x,y,z) with a * x + b * y + c * z + d * 1 < 0 where (x,y,z)
    /// are the coordinates in the camera's space.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float4[] clippingPlanes = []` |
    /// | C++ Type | VtArray<GfVec4f> |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float4Array |
    USDGEOM_API
    UsdAttribute GetClippingPlanesAttr() const;

    /// See GetClippingPlanesAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateClippingPlanesAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FSTOP 
    // --------------------------------------------------------------------- //
    /// Lens aperture. Defaults to 0.0, which turns off focusing.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float fStop = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetFStopAttr() const;

    /// See GetFStopAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateFStopAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // FOCUSDISTANCE 
    // --------------------------------------------------------------------- //
    /// Distance from the camera to the focus plane in scene units; see 
    /// \ref UsdGeom_CameraUnits .
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float focusDistance = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetFocusDistanceAttr() const;

    /// See GetFocusDistanceAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateFocusDistanceAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // STEREOROLE 
    // --------------------------------------------------------------------- //
    /// If different from mono, the camera is intended to be the left
    /// or right camera of a stereo setup.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `uniform token stereoRole = "mono"` |
    /// | C++ Type | TfToken |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Token |
    /// | \ref SdfVariability "Variability" | SdfVariabilityUniform |
    /// | \ref UsdGeomTokens "Allowed Values" | mono, left, right |
    USDGEOM_API
    UsdAttribute GetStereoRoleAttr() const;

    /// See GetStereoRoleAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateStereoRoleAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHUTTEROPEN 
    // --------------------------------------------------------------------- //
    /// Frame relative shutter open time in UsdTimeCode units (negative
    /// value indicates that the shutter opens before the current
    /// frame time). Used for motion blur.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `double shutter:open = 0` |
    /// | C++ Type | double |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
    USDGEOM_API
    UsdAttribute GetShutterOpenAttr() const;

    /// See GetShutterOpenAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateShutterOpenAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // SHUTTERCLOSE 
    // --------------------------------------------------------------------- //
    /// Frame relative shutter close time, analogous comments from
    /// shutter:open apply. A value greater or equal to shutter:open
    /// should be authored, otherwise there is no exposure and a
    /// renderer should produce a black image.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `double shutter:close = 0` |
    /// | C++ Type | double |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Double |
    USDGEOM_API
    UsdAttribute GetShutterCloseAttr() const;

    /// See GetShutterCloseAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateShutterCloseAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // --------------------------------------------------------------------- //
    // EXPOSURE 
    // --------------------------------------------------------------------- //
    /// Exposure adjustment, as a log base-2 value.  The default
    /// of 0.0 has no effect.  A value of 1.0 will double the
    /// image-plane intensities in a rendered image; a value of
    /// -1.0 will halve them.
    ///
    /// | ||
    /// | -- | -- |
    /// | Declaration | `float exposure = 0` |
    /// | C++ Type | float |
    /// | \ref Usd_Datatypes "Usd Type" | SdfValueTypeNames->Float |
    USDGEOM_API
    UsdAttribute GetExposureAttr() const;

    /// See GetExposureAttr(), and also 
    /// \ref Usd_Create_Or_Get_Property for when to use Get vs Create.
    /// If specified, author \p defaultValue as the attribute's default,
    /// sparsely (when it makes sense to do so) if \p writeSparsely is \c true -
    /// the default for \p writeSparsely is \c false.
    USDGEOM_API
    UsdAttribute CreateExposureAttr(VtValue const &defaultValue = VtValue(), bool writeSparsely=false) const;

public:
    // ===================================================================== //
    // Feel free to add custom code below this line, it will be preserved by 
    // the code generator. 
    //
    // Just remember to: 
    //  - Close the class declaration with }; 
    //  - Close the namespace with PXR_NAMESPACE_CLOSE_SCOPE
    //  - Close the include guard with #endif
    // ===================================================================== //
    // --(BEGIN CUSTOM CODE)--

    /// Creates a GfCamera object from the attribute values at \p time.
    ///
    USDGEOM_API
    GfCamera GetCamera(const UsdTimeCode &time) const;

    /// Write attribute values from \p camera for \p time.
    /// These attributes will be updated:
    ///  - projection
    ///  - horizontalAperture
    ///  - horizontalApertureOffset
    ///  - verticalAperture
    ///  - verticalApertureOffset
    ///  - focalLength
    ///  - clippingRange
    ///  - clippingPlanes
    ///  - fStop
    ///  - focalDistance
    ///  - xformOpOrder and xformOp:transform
    /// 
    /// \note This will clear any existing xformOpOrder and replace
    /// it with a single xformOp:transform entry. The xformOp:transform
    /// property is created or updated here to match the transform
    /// on \p camera . This operation will fail if there are stronger xform op
    /// opinions in the composed layer stack that are stronger than that of
    /// the current edit target.
    ///
    USDGEOM_API
    void SetFromCamera(const GfCamera &camera, const UsdTimeCode &time);
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
