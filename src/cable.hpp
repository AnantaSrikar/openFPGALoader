// SPDX-License-Identifier: Apache-2.0
/*
 * Copyright (C) 2019 Gwenhael Goavec-Merou <gwenhael.goavec-merou@trabucayre.com>
 */

#ifndef CABLE_HPP
#define CABLE_HPP

#include <map>
#include <string>

#include "ftdipp_mpsse.hpp"

/*!
 * \brief define type of communication
 */
enum communication_type {
	MODE_ANLOGICCABLE = 0, /*! JTAG probe from Anlogic */
	MODE_CH552_JTAG,       /*! ch552_jtag firmware */
	MODE_FTDI_BITBANG,     /*! used with ft232RL/ft231x */
	MODE_FTDI_SERIAL,      /*! ft2232, ft232H */
	MODE_JLINK,            /*! ft2232, ft232H */
	MODE_DIRTYJTAG,        /*! JTAG probe firmware for STM32F1 */
	MODE_USBBLASTER,       /*! JTAG probe firmware for USBBLASTER */
	MODE_CMSISDAP,         /*! CMSIS-DAP JTAG probe */
	MODE_DFU,              /*! DFU based probe */
	MODE_XVC_CLIENT,       /*! Xilinx Virtual Cable client */
	MODE_LIBGPIOD_BITBANG, /*! Bitbang gpio pins */
	MODE_JETSONNANO_BITBANG, /*! Bitbang gpio pins */
};

typedef struct {
	int type;
	FTDIpp_MPSSE::mpsse_bit_config config;
} cable_t;

static std::map <std::string, cable_t> cable_list = {
	// last 4 bytes are ADBUS7-0 value, ADBUS7-0 direction, ACBUS7-0 value, ACBUS7-0 direction
	// some cables requires explicit values on some of the I/Os
	{"anlogicCable",       {MODE_ANLOGICCABLE, {}}},
	{"arm-usb-ocd-h",      {MODE_FTDI_SERIAL,  {0x15ba, 0x002b, INTERFACE_A, 0x08, 0x1B, 0x09, 0x0B, 0}}},
	{"bus_blaster",        {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x08, 0x1B, 0x08, 0x0B, 0}}},
	{"bus_blaster_b",      {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_B, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"ch552_jtag",         {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"cmsisdap",           {MODE_CMSISDAP,     {0x0d28, 0x0204, 0,           0,    0,    0,    0,    0}}},
	{"gatemate_pgm",       {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0x10, 0x9B, 0x14, 0x17, 0}}},
	{"gatemate_evb_jtag",  {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x10, 0x1B, 0x00, 0x01, 0}}},
	{"gatemate_evb_spi",   {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_B, 0x00, 0x1B, 0x00, 0x01, 0}}},
	{"dfu",                {MODE_DFU,          {}}},
	{"digilent",           {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0xe8, 0xeb, 0x00, 0x60, 0}}},
	{"digilent_b",         {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_B, 0xe8, 0xeb, 0x00, 0x60, 0}}},
	{"digilent_hs2",       {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0xe8, 0xeb, 0x00, 0x60, 0}}},
	{"digilent_hs3",       {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0x88, 0x8B, 0x20, 0x30, 0}}},
	{"digilent_ad",        {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0x08, 0x0B, 0x80, 0x80, 0}}},
	{"dirtyJtag",          {MODE_DIRTYJTAG,    {}}},
	{"efinix_spi_ft4232",  {MODE_FTDI_SERIAL,  {0x0403, 0x6011, INTERFACE_A, 0x08, 0x8B, 0x00, 0x00, 0}}},
	{"efinix_jtag_ft4232", {MODE_FTDI_SERIAL,  {0x0403, 0x6011, INTERFACE_B, 0x08, 0x8B, 0x00, 0x00, 0}}},
	{"efinix_spi_ft2232",  {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x08, 0x8B, 0x00, 0x00, 0}}},
	{"ft2232",             {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"ft2232_b",           {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_B, 0x08, 0x0B, 0x00, 0x00, 0}}},
	{"ft231X",             {MODE_FTDI_BITBANG, {0x0403, 0x6015, INTERFACE_A, 0x00, 0x00, 0x00, 0x00, 0}}},
	{"ft232",              {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"ft232RL",            {MODE_FTDI_BITBANG, {0x0403, 0x6001, INTERFACE_A, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"ft4232",             {MODE_FTDI_SERIAL,  {0x0403, 0x6011, INTERFACE_A, 0x08, 0x0B, 0x08, 0x0B, 0}}},
	{"ecpix5-debug",       {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0xF8, 0xFB, 0xFF, 0xFF, 0}}},
	{"jlink",              {MODE_JLINK,        {0x1366, 0x0105, 0,           0,    0,    0,    0,    0}}},
	{"jtag-smt2-nc",       {MODE_FTDI_SERIAL,  {0x0403, 0x6014, INTERFACE_A, 0xe8, 0xeb, 0x00, 0x60, 0}}},
	{"lpc-link2",          {MODE_CMSISDAP,     {0x1fc9, 0x0090, 0,           0,    0,    0,    0,    0}}},
	{"orbtrace",           {MODE_CMSISDAP,     {0x1209, 0x3443, 0,           0,    0,    0,    0,    0}}},
	{"papilio",            {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x08, 0x0B, 0x09, 0x0B, 0}}},
	{"steppenprobe",       {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_A, 0x58, 0xFB, 0x00, 0x99, 0}}},
	{"tigard",             {MODE_FTDI_SERIAL,  {0x0403, 0x6010, INTERFACE_B, 0x08, 0x3B, 0x00, 0x00, 0}}},
	{"usb-blaster",        {MODE_USBBLASTER,   {0x09Fb, 0x6001, 0,           0,    0,    0,    0,    0}}},
	{"usb-blasterII",      {MODE_USBBLASTER,   {0x09Fb, 0x6810, 0,           0,    0,    0,    0,    0}}},
	{"xvc-client",         {MODE_XVC_CLIENT,   {}}},
#ifdef ENABLE_LIBGPIOD
	{"libgpiod",           {MODE_LIBGPIOD_BITBANG, {}}},
#endif
#ifdef ENABLE_JETSONNANOGPIO
	{"jetson-nano-gpio",   {MODE_JETSONNANO_BITBANG, {}}},
#endif
};

#endif
