// The battle's particle effects (pcp_field_controls.c in legacy/): their
// setters. Rewritten from the original instructions.
#include "nocturne/effect/particles.hpp"

#include "nocturne/address.hpp"
#include "nocturne/guest.hpp"

namespace nocturne::eff {

static_assert(sizeof(Matrix) == 0x40);

namespace {

constexpr uint32_t kBlinkMultiBlur = addr(0x00551dd0);   // the blink effect playing (gp-relative)

template <class T> T& field(uint32_t effect, uint32_t offset) { return *guest::table<T>(effect + offset); }
uint32_t word(uint32_t address) { return *guest::table<const uint32_t>(address); }
void place(uint32_t effect, uint32_t offset, const dds3::Vector4& position) { field<dds3::Vector4>(effect, offset) = position; }

} // namespace

// effPCPFlashPolySphere2SetPosition @ 0x0017D228
// effPCPFlashPolySphereSetPosition @ 0x0017D8D8
// effPCPFlashPolyRingSetPosition @ 0x0017E290
// effPCPFlashPolyPipeSetPosition @ 0x0017EAB8
// effPCPFlashPolyRingExpSetPosition @ 0x0017F3B8
// effPCPHamaCardSpiralSetPosition @ 0x00184528
// effPCPHamaCardSphereSetPosition @ 0x00185138
// effPCPSparkleSphereSetPosition @ 0x0018A340
// effPCPMHanma01SetPosition @ 0x0018B630
// effPCPHwave01SetPosition @ 0x0018BCF0
// effPCPZiodin01SetPosition @ 0x0018C180
// effPCPZiodin02SetPosition @ 0x0018C5F8
// effPCPZiodin03SetPosition @ 0x0018CA90
// effPCPZiodin04SetPosition @ 0x0018CF08
// effPCPMZiodin01SetPosition @ 0x0018D278
// effPCPMZiodin02SetPosition @ 0x0018D5E8
// effPCPShockWave01SetPosition @ 0x0018D838
// effPCPShockWave02SetPosition @ 0x0018DCD0
// effPCPHouden01SetPosition @ 0x0018DF18
// effPCPMultiBlurExpSetPosition @ 0x0018E370
// effPCPMultiFilterExpSetPosition @ 0x0018E6B8
// effPCPMultiBlurExp2SetPosition @ 0x0018EA10
// effPCPDistortionBlurExpSetPosition @ 0x0018F1A0
// effPCPMegidora01SetPosition @ 0x0018F7E0
// effPCPMegidoraon01SetPosition @ 0x0018FA88
// effPCPAgiraoFireSetPosition @ 0x001904E8
// effPCPBufuIceSetPosition @ 0x00192420
// effPCPBufuraIceSetPosition @ 0x00192720
// effPCPBufudnIceSetPosition @ 0x00192A20
// effPCPThunderSpherePolySetPosition @ 0x00176520
// effPCP_ThunderRadiatePolySetPosition @ 0x00179B38
// effPCPHama01SetPosition @ 0x0018A898
// effPCPHama02SetPosition @ 0x0018AD18
// effPCPHamaonSetPosition @ 0x0018B2A8
// Most effects keep their position at the start of their work.
void setPosition(uint32_t effect, const dds3::Vector4& position) { place(effect, 0, position); }

// effPCP_ThunderPolyLowSetPosition @ 0x00179118
// effPCP_ThunderPolySetPosition @ 0x00178618
// The thunder effects keep the position they were given at +0x10 and move
// their own (at the start) by as much.
void setThunderPolyPosition(uint32_t effect, const dds3::Vector4& position)
{
    dds3::Vector4& given = field<dds3::Vector4>(effect, 0x10);
    const dds3::Vector4 by{position.x - given.x, position.y - given.y, position.z - given.z, position.w - given.w};
    given = position;
    dds3::Vector4& own = field<dds3::Vector4>(effect, 0);
    own = {own.x + by.x, own.y + by.y, own.z + by.z, own.w + by.w};
}

// effPCP_ThunderPolyLowSetColor @ 0x00179148
void setThunderPolyLowColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x58) = color; }

// effPCPFlashPolySphere2SetColor @ 0x0017D238
void setFlashPolySphere2Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x38) = color; }

// effPCPFlashPolySphere2SetScale @ 0x0017D240
void setFlashPolySphere2Scale(uint32_t effect, ee::Float scale) { field<ee::Float>(effect, 0x3c) = scale; }

// effPCPFlashPolySphereSetColor @ 0x0017D8E8
void setFlashPolySphereColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x48) = color; }

// effPCPFlashPolyRingSetColor @ 0x0017E2A0
void setFlashPolyRingColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x50) = color; }

// effPCPFlashPolyPipeSetColor @ 0x0017EAC8
void setFlashPolyPipeColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x58) = color; }

// effPCPFlashPolyRingExpSetColor @ 0x0017F3C8
void setFlashPolyRingExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x60) = color; }

// effPCPHamaCardSpiralSetColor @ 0x00184538
void setHamaCardSpiralColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x7c) = color; }

// effPCPHamaCardSpiralSetScale @ 0x00184540: scales its sizes (it has no scale of its own).
void setHamaCardSpiralScale(uint32_t effect, ee::Float scale)
{
    for (const uint32_t size : {0x3cu, 0x4cu, 0x50u})
        field<ee::Float>(effect, size) = field<ee::Float>(effect, size) * scale;
}

// effPCPHamaCardSphereSetColor @ 0x00185148
void setHamaCardSphereColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x6c) = color; }

// effPCPHamaCardSphereSetScale @ 0x00185150: scales its sizes (it has no scale of its own).
void setHamaCardSphereScale(uint32_t effect, ee::Float scale)
{
    for (const uint32_t size : {0x40u, 0x44u})
        field<ee::Float>(effect, size) = field<ee::Float>(effect, size) * scale;
}

// effPCPSparkleSphereSetColor @ 0x0018A350
void setSparkleSphereColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPMHanma01SetColor @ 0x0018B648
void setMahama01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPHwave01SetColor @ 0x0018BD00
void setHwave01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPZiodin01SetColor @ 0x0018C198
void setZiodyne01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPZiodin02SetColor @ 0x0018C610
void setZiodyne02Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPZiodin03SetColor @ 0x0018CAA8
void setZiodyne03Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPZiodin04SetColor @ 0x0018CF20
void setZiodyne04Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPMZiodin01SetColor @ 0x0018D290
void setMaziodyne01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPMZiodin02SetColor @ 0x0018D600
void setMaziodyne02Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPShockWave01SetColor @ 0x0018D850
void setShockWave01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPShockWave02SetColor @ 0x0018DCE8
void setShockWave02Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x18) = color; }

// effPCPHouden01SetColor @ 0x0018DF30
void setDischarge01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPBlinkMultiBlurSetPosition @ 0x0018E190: the one blink effect playing (not `effect`).
void setBlinkMultiBlurPosition(uint32_t, const dds3::Vector4& position) { place(word(kBlinkMultiBlur), 0, position); }

// effPCPBlinkMultiBlurSetColor @ 0x0018E1A8: the one blink effect playing (not `effect`).
void setBlinkMultiBlurColor(uint32_t, uint32_t color) { field<uint32_t>(word(kBlinkMultiBlur), 0x10) = color; }

// effPCPMultiBlurExpSetColor @ 0x0018E380
void setMultiBlurExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPMultiFilterExpSetColor @ 0x0018E6C8
void setMultiFilterExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPMultiBlurExp2SetColor @ 0x0018EA20
void setMultiBlurExp2Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPFilterExpSetColor @ 0x0018EC20
void setFilterExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x24) = color; }

// effPCPBlurExpSetColor @ 0x0018EE40
void setBlurExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x34) = color; }

// effPCPDistortionBlurExpSetColor @ 0x0018F1B0
void setDistortionBlurExpColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x20) = color; }

// effPCPMegidora01SetColor @ 0x0018F7F8
void setMegidola01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPMegidoraon01SetColor @ 0x0018FAA0
void setMegidolaon01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x14) = color; }

// effPCPBreathSetPosition @ 0x0018FEF8: its position after a 0x40-byte header.
void setBreathPosition(uint32_t effect, const dds3::Vector4& position) { place(effect, 0x40, position); }

// effPCPBreathSetColor @ 0x0018FF10
void setBreathColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x64) = color; }

// effPCPAgiraoFireSetColor @ 0x001904F8
void setAgilaoFireColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x54) = color; }

// effPCPBufuIceSetColor @ 0x00192430
void setBufuIceColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x5c) = color; }

// effPCPBufuraIceSetColor @ 0x00192730
void setBufulaIceColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x5c) = color; }

// effPCPBufudnIceSetColor @ 0x00192A30
void setBufudyneIceColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x5c) = color; }

// effPCPBufuIceSetScale @ 0x00192438
// effPCPBufuraIceSetScale @ 0x00192738
// effPCPBufudnIceSetScale @ 0x00192A38
// The ice effects (Bufu, Bufula, Bufudyne) share their layout.
void setIceScale(uint32_t effect, ee::Float scale) { field<ee::Float>(effect, 0x58) = scale; }

// effPCPBufuIceSetRotateMatrix @ 0x00192440
// effPCPBufuraIceSetRotateMatrix @ 0x00192740
// effPCPBufudnIceSetRotateMatrix @ 0x00192A40
void setIceRotation(uint32_t effect, const Matrix& rotation) { field<Matrix>(effect, 0x10) = rotation; }

// effPCPThunderSpherePolySetColor @ 0x00176530
void setThunderSpherePolyColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x50) = color; }

// effPCP_ThunderPolySetColor @ 0x00178648
void setThunderPolyColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x58) = color; }

// effPCP_ThunderRadiatePolySetColor @ 0x00179B48
void setThunderRadiatePolyColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x4c) = color; }

// effPCPHama01SetColor @ 0x0018A8B0
void setHama01Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPHama02SetColor @ 0x0018AD30
void setHama02Color(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPHamaonSetColor @ 0x0018B2C0
void setHamaonColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x10) = color; }

// effPCPMudoSetColor @ 0x0018BB58
void setMudoColor(uint32_t effect, uint32_t color) { field<uint32_t>(effect, 0x1334) = color; }

// effPCPMudoSetPosition @ 0x0018BB38
void setMudoPosition(uint32_t effect, const dds3::Vector4& position) { place(effect, 0xaf0, position); }

// effPCPMudoSetScale @ 0x0018BB50
void setMudoScale(uint32_t effect, ee::Float scale) { field<ee::Float>(effect, 0x1338) = scale; }

// effPCPHama01SetScale @ 0x0018A8A8
void setHama01Scale(uint32_t effect, ee::Float scale) { field<ee::Float>(effect, 0x18) = scale; }

// effPCPHama02SetScale @ 0x0018AD28
// effPCPHamaonSetScale @ 0x0018B2B8
void setHama02Scale(uint32_t effect, ee::Float scale) { field<ee::Float>(effect, 0x14) = scale; }

// effPCPSparkleSphereSetArea @ 0x0018A358
void setSparkleSphereArea(uint32_t effect, ee::Float area) { field<ee::Float>(effect, 0x18) = area; }

// effPCPBlinkMultiBlurSetArea @ 0x0018E1B8: the one blink effect playing (not `effect`).
void setBlinkMultiBlurArea(uint32_t, ee::Float area) { field<ee::Float>(word(kBlinkMultiBlur), 0x1c) = area; }

// effPCPMultiBlurExpSetArea @ 0x0018E388
void setMultiBlurExpArea(uint32_t effect, ee::Float area) { field<ee::Float>(effect, 0x1c) = area; }

// effPCPMultiFilterExpSetArea @ 0x0018E6D0
void setMultiFilterExpArea(uint32_t effect, ee::Float area) { field<ee::Float>(effect, 0x34) = area; }

} // namespace nocturne::eff
