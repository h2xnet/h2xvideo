#ifndef H2XVIDEO_APP_CACHE__H
#define H2XVIDEO_APP_CACHE__H

#include "h2xcore/h2x_cache.h"

#include "h2xvideo/cache/router_cache.h"

/*
 * ClassName: AppCache
 * Desc: 应用缓存类
 * Author: zfs
 * Date: 2021-06-12 22:51
 */
class AppCache : public h2x::Cache {
public:
    AppCache();
    virtual ~AppCache();

    RouterCache& getRouterCache() {
        return router_cache_;
    }

public:

    // 路由缓存
    RouterCache router_cache_;
};

#endif // !H2XVIDEO_APP_CACHE__H
