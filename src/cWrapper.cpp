// Copyright 2019 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/cWrapper.h"
#include "wsiToDcm.h"

int wsi2dcm(const char *inputFile, const char *outputFileMask,
            int64_t frameSizeX, int64_t frameSizeY, const char *compression,
            int quality, int startOnLevel, int stopOnLevel,
            const char *imageName, const char *studyId, const char *seriesId,
            int retileLevels, double *downsamples, bool tiled, int batchLimit,
            int threads, bool debug) {
  return wsi2dcmJson(
      inputFile, outputFileMask, frameSizeX, frameSizeY, compression, quality,
      startOnLevel, stopOnLevel, imageName, studyId, seriesId, "", retileLevels,
      downsamples, tiled, batchLimit, threads, debug);
}

int wsi2dcmJson(const char *inputFile, const char *outputFileMask,
                int64_t frameSizeX, int64_t frameSizeY, const char *compression,
                int quality, int startOnLevel, int stopOnLevel,
                const char *imageName, const char *studyId,
                const char *seriesId, const char *jsonFile, int retileLevels,
                double *downsamples, bool tiled, int batchLimit, int threads,
                bool debug) {
  wsiToDicomConverter::WsiRequest request;
  request.inputFile = inputFile;
  request.outputFileMask = outputFileMask;
  request.frameSizeX = frameSizeX;
  request.frameSizeY = frameSizeY;
  request.compression = dcmCompressionFromString(compression);
  request.quality = quality;
  request.startOnLevel = startOnLevel;
  request.stopOnLevel = stopOnLevel;
  request.imageName = imageName;
  request.studyId = studyId;
  request.seriesId = seriesId;
  request.jsonFile = jsonFile;
  request.retileLevels = retileLevels;
  request.downsamples = &downsamples[0];
  request.tiled = tiled;
  request.batchLimit = batchLimit;
  request.threads = threads;
  request.debug = debug;
  return wsiToDicomConverter::WsiToDcm::wsi2dcm(request);
}
