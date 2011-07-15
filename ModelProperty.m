//
//  ModelProperty.m
//  TrenchBroom
//
//  Created by Kristian Duske on 23.04.11.
//  Copyright 2011 TU Berlin. All rights reserved.
//

#import "ModelProperty.h"


@implementation ModelProperty

- (id)initWithModelPath:(NSString *)theModelPath {
    NSAssert(theModelPath != nil, @"model path must not be nil");
    
    if ((self = [self init])) {
        modelPath = [theModelPath retain];
    }
    
    return self;
}

- (id)initWithModelPath:(NSString *)theModelPath skinIndex:(int)theSkinIndex {
    NSAssert(theModelPath != nil, @"model path must not be nil");
    NSAssert(theSkinIndex >= 0, @"skin index must be at least 0");
    
    if ((self = [self init])) {
        modelPath = [theModelPath retain];
        skinIndex = theSkinIndex;
    }
    
    return self;
}

- (id)initWithFlagName:(NSString *)theFlagName modelPath:(NSString *)theModelPath {
    NSAssert(theFlagName != nil, @"flag name must not be nil");
    NSAssert(theModelPath != nil, @"model path must not be nil");
    
    if ((self = [self init])) {
        flagName = [theFlagName retain];
        modelPath = [theModelPath retain];
    }
    
    return self;
}

- (id)initWithFlagName:(NSString *)theFlagName modelPath:(NSString *)theModelPath skinIndex:(int)theSkinIndex {
    NSAssert(theFlagName != nil, @"flag name must not be nil");
    NSAssert(theModelPath != nil, @"model path must not be nil");
    NSAssert(theSkinIndex >= 0, @"skin index must be at least 0");
    
    if ((self = [self init])) {
        flagName = [theFlagName retain];
        modelPath = [theModelPath retain];
        skinIndex = theSkinIndex;
    }
    
    return self;
}

- (void)dealloc {
    [modelPath release];
    [super dealloc];
}

- (EEntityDefinitionPropertyType)type {
    return EDP_MODEL;
}

- (NSString *)flagName {
    return flagName;
}

- (NSString *)modelPath {
    return modelPath;
}

- (int)skinIndex {
    return skinIndex;
}

- (NSString *)description {
    NSMutableString* desc = [[NSMutableString alloc] initWithString:modelPath];
    [desc appendFormat:@", skin: ", skinIndex];
    if (flagName != nil)
        [desc appendFormat:@", flag: ", flagName];

    return [desc autorelease];
}

@end