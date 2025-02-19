/**
    bespoke synth, a software modular synthesizer
    Copyright (C) 2021 Ryan Challinor (contact: awwbees@gmail.com)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**/
/*
  ==============================================================================

    TransposeFrom.h
    Created: 14 Jul 2021 7:47:48pm
    Author:  Ryan Challinor

  ==============================================================================
*/

#pragma once
#include <iostream>

#include "NoteEffectBase.h"
#include "IDrawableModule.h"
#include "Checkbox.h"
#include "DropdownList.h"
#include "Scale.h"

class TransposeFrom : public NoteEffectBase, public IDrawableModule, public IDropdownListener, public IScaleListener
{
public:
   TransposeFrom();
   virtual ~TransposeFrom();
   static IDrawableModule* Create() { return new TransposeFrom(); }
   
   
   void CreateUIControls() override;
   
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   //INoteReceiver
   void PlayNote(double time, int pitch, int velocity, int voiceIdx = -1, ModulationParameters modulation = ModulationParameters()) override;
   
   //IScaleListener
   void OnScaleChanged() override;
   
   void CheckboxUpdated(Checkbox* checkbox) override;
   void DropdownUpdated(DropdownList* list, int oldVal) override;
   
   virtual void LoadLayout(const ofxJSONElement& moduleInfo) override;
   virtual void SetUpFromSaveData() override;
   
private:
   struct NoteInfo
   {
      NoteInfo() : mOn(false), mVelocity(0), mVoiceIdx(-1) {}
      bool mOn;
      int mVelocity;
      int mVoiceIdx;
      int mOutputPitch;
   };
   
   //IDrawableModule
   void DrawModule() override;
   void GetModuleDimensions(float& width, float& height) override { width = mWidth; height = mHeight; }
   bool Enabled() const override { return mEnabled; }
   
   int GetTransposeAmount() const;
   void OnRootChanged();
   
   float mWidth;
   float mHeight;
   int mRoot;
   DropdownList* mRootSelector;
   std::array<NoteInfo, 128> mInputNotes;
   Checkbox* mRetriggerCheckbox;
   bool mRetrigger;
};
