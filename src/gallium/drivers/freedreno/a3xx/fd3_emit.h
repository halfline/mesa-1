/* -*- mode: C; c-file-style: "k&r"; tab-width 4; indent-tabs-mode: t; -*- */

/*
 * Copyright (C) 2013 Rob Clark <robclark@freedesktop.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * Authors:
 *    Rob Clark <robclark@freedesktop.org>
 */

#ifndef FD3_EMIT_H
#define FD3_EMIT_H

#include "pipe/p_context.h"

#include "freedreno_context.h"
#include "fd3_format.h"
#include "fd3_program.h"
#include "ir3_shader.h"

struct fd_ringbuffer;
enum adreno_state_block;

void fd3_emit_constant(struct fd_ringbuffer *ring,
		enum adreno_state_block sb,
		uint32_t regid, uint32_t offset, uint32_t sizedwords,
		const uint32_t *dwords, struct pipe_resource *prsc);

void fd3_emit_gmem_restore_tex(struct fd_ringbuffer *ring,
		struct pipe_surface *psurf);

/* grouped together emit-state for prog/vertex/state emit: */
struct fd3_emit {
	const struct fd_vertex_state *vtx;
	const struct fd_program_stateobj *prog;
	const struct pipe_draw_info *info;
	struct ir3_shader_key key;
	enum pipe_format format;
	uint32_t dirty;
	bool rasterflat;

	/* cached to avoid repeated lookups of same variants: */
	struct ir3_shader_variant *vp, *fp;
};

static inline struct ir3_shader_variant *
fd3_emit_get_vp(struct fd3_emit *emit)
{
	if (!emit->vp) {
		struct fd3_shader_stateobj *so = emit->prog->vp;
		emit->vp = ir3_shader_variant(so->shader, emit->key);
	}
	return emit->vp;
}

static inline struct ir3_shader_variant *
fd3_emit_get_fp(struct fd3_emit *emit)
{
	if (!emit->fp) {
		struct fd3_shader_stateobj *so = emit->prog->fp;
		emit->fp = ir3_shader_variant(so->shader, emit->key);
	}
	return emit->fp;
}

void fd3_emit_vertex_bufs(struct fd_ringbuffer *ring, struct fd3_emit *emit);

void fd3_emit_state(struct fd_context *ctx, struct fd_ringbuffer *ring,
		struct fd3_emit *emit);

void fd3_emit_restore(struct fd_context *ctx);

#endif /* FD3_EMIT_H */
