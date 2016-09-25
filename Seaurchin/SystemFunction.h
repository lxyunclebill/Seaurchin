#pragma once

#include "DxLibResouce.h"

std::shared_ptr<Image> LoadSystemImage(const std::string & file);
std::shared_ptr<Font> LoadSystemFont(const std::string & file);
std::shared_ptr<VirtualFont> CreateVirtualFont(const std::string & name, int size);
void CreateImageFont(const std::string & fileName, const std::string & saveName, int size);
void DrawRawString(std::shared_ptr<VirtualFont> font, const std::string &str, double x, double y);
void EnumerateInstalledFonts();