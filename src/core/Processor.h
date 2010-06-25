/*
Copyright (c) 2003-2010 Sony Pictures Imageworks Inc., et al.
All Rights Reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
* Redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution.
* Neither the name of Sony Pictures Imageworks nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#ifndef INCLUDED_OCIO_PROCESSOR_H
#define INCLUDED_OCIO_PROCESSOR_H

#include <OpenColorIO/OpenColorIO.h>

#include "Op.h"

OCIO_NAMESPACE_ENTER
{
    class LocalProcessor : public Processor
    {
    public:
        static ConstProcessorRcPtr Create(const OpRcPtrVec& opVec);
        
        virtual ~LocalProcessor();
        
        virtual bool isNoOp() const;
        
        virtual void apply(ImageDesc& img) const;
        
        virtual void applyRGB(float * pixel) const;
        virtual void applyRGBA(float * pixel) const;
        
        virtual const char * getGPUShaderText(const GpuShaderDesc & gpuDesc) const;
        
        /*
        virtual int getGPULut3DEdgeLen() const;
        virtual const char * getGPULut3DCacheID(const GpuShaderDesc & gpuDesc) const;
        virtual void getGPULut3D(float* lut3d, const GpuShaderDesc & gpuDesc) const;
        */
        
    private:
        LocalProcessor(const OpRcPtrVec& opVec);
        LocalProcessor(const LocalProcessor &);
        LocalProcessor& operator= (const LocalProcessor &);
        
        static void deleter(LocalProcessor* p);
        
        void getGPUShader(std::ostringstream * shader,
                          std::ostringstream * lut3dCacheID, float * lut3d,
                          const GpuShaderDesc & gpuDesc) const;
        
        OpRcPtrVec m_opVec;
        
        mutable std::string m_shaderText;
    };
    
    
}
OCIO_NAMESPACE_EXIT

#endif